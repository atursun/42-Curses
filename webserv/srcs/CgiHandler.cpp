/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:00:00 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/15 17:02:58 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"
#include <sys/wait.h>
#include <sstream>
#include <csignal>
#include <cstdio>

static std::string resolveAbsPath(const std::string& path)
{
    if (!path.empty() && path[0] == '/')
        return path;
    char cwd[4096];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return path;
    return std::string(cwd) + "/" + path;
}

static std::string extractHeaderVal(const std::string& raw_request, const std::string& name)
{
    std::string search = name + ":";
    size_t pos = raw_request.find(search);
    if (pos == std::string::npos)
        return "";
    pos += search.size();
    while (pos < raw_request.size() && (raw_request[pos] == ' ' || raw_request[pos] == '\t'))
        pos++;
    size_t end = raw_request.find("\r\n", pos);
    if (end == std::string::npos)
        end = raw_request.find("\n", pos);
    if (end == std::string::npos)
        return raw_request.substr(pos);
    return raw_request.substr(pos, end - pos);
}

static std::vector<std::string> buildEnvStrings(
    const std::string& method,
    const std::string& query_string,
    const std::string& abs_file_path,
    const std::string& script_name,
    const std::string& content_type,
    const std::string& content_length,
    const std::string& srv_name,
    int srv_port,
    const std::string& raw_request)
{
    std::vector<std::string> env;
    std::stringstream port_ss;
    port_ss << srv_port;

    env.push_back("REQUEST_METHOD=" + method);
    env.push_back("QUERY_STRING=" + query_string);
    env.push_back("CONTENT_TYPE=" + content_type);
    env.push_back("CONTENT_LENGTH=" + content_length);
    env.push_back("SCRIPT_FILENAME=" + abs_file_path);
    env.push_back("SCRIPT_NAME=");
    env.push_back("PATH_INFO=" + script_name);
    env.push_back("PATH_TRANSLATED=" + abs_file_path);
    env.push_back("SERVER_NAME=" + (srv_name.empty() ? std::string("localhost") : srv_name));
    env.push_back("SERVER_PORT=" + port_ss.str());
    env.push_back("SERVER_PROTOCOL=HTTP/1.1");
    env.push_back("GATEWAY_INTERFACE=CGI/1.1");
    env.push_back("SERVER_SOFTWARE=webserv/1.0");
    env.push_back("REDIRECT_STATUS=200");
    
    size_t header_end = raw_request.find("\r\n\r\n");
    if (header_end == std::string::npos)
        header_end = raw_request.find("\n\n");
    if (header_end != std::string::npos)
    {
        size_t line_start = raw_request.find("\r\n");
        if (line_start == std::string::npos)
            line_start = raw_request.find("\n");
        if (line_start != std::string::npos)
        {
            line_start += (raw_request[line_start] == '\r') ? 2 : 1;
            std::string headers_part = raw_request.substr(line_start, header_end - line_start);
            std::istringstream hstream(headers_part);
            std::string hline;
            while (std::getline(hstream, hline))
            {
                if (!hline.empty() && hline[hline.size() - 1] == '\r')
                    hline.resize(hline.size() - 1);
                if (hline.empty())
                    continue;
                size_t colon = hline.find(':');
                if (colon == std::string::npos)
                    continue;
                std::string key = hline.substr(0, colon);
                std::string val = hline.substr(colon + 1);
                while (!val.empty() && (val[0] == ' ' || val[0] == '\t'))
                    val = val.substr(1);
                std::string env_key = "HTTP_";
                for (size_t k = 0; k < key.size(); k++)
                {
                    if (key[k] == '-')
                        env_key += '_';
                    else
                        env_key += (char)toupper((unsigned char)key[k]);
                }
                env.push_back(env_key + "=" + val);
            }
        }
    }
    return env;
}

LocationConfig* ServerConfig::findCgiLocation(const std::string& request_path)
{
    std::string ext;
    size_t dot_pos = request_path.rfind('.');
    size_t slash_pos = request_path.rfind('/');
    size_t q_pos = request_path.find('?');
    std::string path_no_qs = (q_pos != std::string::npos) ? request_path.substr(0, q_pos) : request_path;
    dot_pos = path_no_qs.rfind('.');
    slash_pos = path_no_qs.rfind('/');
    if (dot_pos != std::string::npos &&
        (slash_pos == std::string::npos || dot_pos > slash_pos))
        ext = path_no_qs.substr(dot_pos);

    if (ext.empty())
        return NULL;

    for (size_t i = 0; i < locations.size(); i++)
    {
        if (!locations[i].cgi_ext.empty() && locations[i].cgi_ext == ext)
            return &locations[i];
    }
    return NULL;
}

void ServerConfig::handle_cgi(
    std::string raw_request,
    std::string request_path,
    std::string file_path,
    LocationConfig* cgi_loc,
    std::string method,
    int fd)
{
    std::string query_string;
    std::string script_name = request_path;
    size_t q_pos = request_path.find('?');
    if (q_pos != std::string::npos)
    {
        script_name = request_path.substr(0, q_pos);
        query_string = request_path.substr(q_pos + 1);
    }

    std::string body;
    size_t body_start = raw_request.find("\r\n\r\n");
    if (body_start != std::string::npos)
        body = raw_request.substr(body_start + 4);

    std::string content_type = extractHeaderVal(raw_request, "Content-Type");
    std::string content_length = extractHeaderVal(raw_request, "Content-Length");
    if (content_length.empty()) {
        std::stringstream cl_ss;
        cl_ss << body.size();
        content_length = cl_ss.str();
    }
    {
        std::stringstream cl_trim_ss(content_length);
        size_t cl_val = 0;
        cl_trim_ss >> cl_val;
        if (cl_val < body.size())
            body.resize(cl_val);
    }

    std::string abs_file_path = resolveAbsPath(file_path);
    std::string exec_path;

    if (!cgi_loc->cgi_path.empty())
        exec_path = resolveAbsPath(cgi_loc->cgi_path);
    else
        exec_path = abs_file_path;

    std::string script_dir = abs_file_path.substr(0, abs_file_path.rfind('/'));
    if (script_dir.empty())
        script_dir = "/";

    if (access(exec_path.c_str(), X_OK) != 0)
    {
        std::cerr << "CGI executable not accessible: " << exec_path << std::endl;
        Send500(abs_file_path, fd);
        return;
    }

    std::vector<std::string> env_strs = buildEnvStrings(
        method, query_string, abs_file_path, script_name,
        content_type, content_length,
        server_name, port, raw_request);

    std::vector<char*> envp;
    for (size_t i = 0; i < env_strs.size(); i++)
        envp.push_back(const_cast<char*>(env_strs[i].c_str()));
    envp.push_back(NULL);

    std::vector<std::string> arg_strs;
    arg_strs.push_back(exec_path);
    if (!cgi_loc->cgi_path.empty())
        arg_strs.push_back(abs_file_path);

    std::vector<char*> argv_vec;
    for (size_t i = 0; i < arg_strs.size(); i++)
        argv_vec.push_back(const_cast<char*>(arg_strs[i].c_str()));
    argv_vec.push_back(NULL);

    FILE* stdin_tmp = tmpfile();
    FILE* stdout_tmp = tmpfile();
    if (stdin_tmp == NULL || stdout_tmp == NULL)
    {
        if (stdin_tmp != NULL)
            fclose(stdin_tmp);
        if (stdout_tmp != NULL)
            fclose(stdout_tmp);
        std::cerr << "CGI tmpfile failed" << std::endl;
        Send500(abs_file_path, fd);
        return;
    }

    int stdin_fd = fileno(stdin_tmp);
    int stdout_fd = fileno(stdout_tmp);
    if (stdin_fd < 0 || stdout_fd < 0)
    {
        fclose(stdin_tmp);
        fclose(stdout_tmp);
        std::cerr << "CGI fileno failed" << std::endl;
        Send500(abs_file_path, fd);
        return;
    }

    if (!body.empty())
    {
        size_t body_written = 0;
        while (body_written < body.size())
        {
            ssize_t w = write(stdin_fd,
                              body.c_str() + body_written,
                              body.size() - body_written);
            if (w <= 0)
            {
                fclose(stdin_tmp);
                fclose(stdout_tmp);
                std::cerr << "CGI tmp stdin write failed" << std::endl;
                Send500(abs_file_path, fd);
                return;
            }
            body_written += (size_t)w;
        }
    }
    lseek(stdin_fd, 0, SEEK_SET);

    pid_t pid = fork();
    if (pid < 0)
    {
        fclose(stdin_tmp);
        fclose(stdout_tmp);
        std::cerr << "CGI fork failed" << std::endl;
        Send500(abs_file_path, fd);
        return;
    }

    if (pid == 0)
    {
        if (dup2(stdin_fd, STDIN_FILENO) < 0)
            exit(1);
        if (dup2(stdout_fd, STDOUT_FILENO) < 0)
            exit(1);
        dup2(stdout_fd, STDERR_FILENO);

        fclose(stdin_tmp);
        fclose(stdout_tmp);

        if (chdir(script_dir.c_str()) < 0)
        {
            std::cerr << "CGI chdir failed: " << script_dir << std::endl;
            exit(1);
        }

        execve(exec_path.c_str(), &argv_vec[0], &envp[0]);
        std::cerr << "CGI execve failed: " << exec_path << std::endl;
        exit(1);
    }

    fclose(stdin_tmp);

    struct sigaction sa_old;
    struct sigaction sa_ign;
    sa_ign.sa_handler = SIG_IGN;
    sigemptyset(&sa_ign.sa_mask);
    sa_ign.sa_flags = 0;
    sigaction(SIGPIPE, &sa_ign, &sa_old);

    std::string cgi_output;
    char io_buf[8192];
    time_t start = time(NULL);
    long cgi_timeout = 30;
    int child_status = 0;
    bool child_done = false;
    bool timeout_hit = false;

    if (body.size() > (size_t)(1024 * 1024))
    {
        cgi_timeout += (long)(body.size() / (size_t)(5 * 1024 * 1024));
        if (cgi_timeout > 180)
            cgi_timeout = 180;
    }

    while (!child_done)
    {
        if (time(NULL) - start > cgi_timeout)
        {
            std::cerr << "CGI timeout!" << std::endl;
            kill(pid, SIGKILL);
            waitpid(pid, &child_status, 0);
            child_done = true;
            timeout_hit = true;
            break;
        }
        pid_t wpid = waitpid(pid, &child_status, WNOHANG);
        if (wpid == pid)
            child_done = true;
    }

    lseek(stdout_fd, 0, SEEK_SET);
    ssize_t rr;
    while ((rr = read(stdout_fd, io_buf, sizeof(io_buf))) > 0)
        cgi_output.append(io_buf, (size_t)rr);

    fclose(stdout_tmp);

    if (timeout_hit)
    {
        sigaction(SIGPIPE, &sa_old, NULL);
        Send500(abs_file_path, fd);
        return;
    }

    sigaction(SIGPIPE, &sa_old, NULL);

    std::string http_status = "200 OK";
    std::string cgi_headers_str;
    std::string cgi_body;

    size_t blank = cgi_output.find("\r\n\r\n");
    bool is_crlf = true;
    if (blank == std::string::npos)
    {
        blank = cgi_output.find("\n\n");
        is_crlf = false;
    }

    if (blank != std::string::npos)
    {
        cgi_headers_str = cgi_output.substr(0, blank);
        cgi_body = cgi_output.substr(blank + (is_crlf ? 4 : 2));
    }
    else
    {
        cgi_body = cgi_output;
    }

    size_t status_pos = cgi_headers_str.find("Status:");
    if (status_pos != std::string::npos)
    {
        size_t sv = status_pos + 7;
        while (sv < cgi_headers_str.size() &&
               (cgi_headers_str[sv] == ' ' || cgi_headers_str[sv] == '\t'))
            sv++;
        size_t se = cgi_headers_str.find('\n', sv);
        if (se == std::string::npos)
            se = cgi_headers_str.size();
        http_status = cgi_headers_str.substr(sv, se - sv);
        if (!http_status.empty() && http_status[http_status.size() - 1] == '\r')
            http_status.resize(http_status.size() - 1);
        size_t line_end = cgi_headers_str.find('\n', status_pos);
        if (line_end != std::string::npos)
            cgi_headers_str.erase(status_pos, line_end - status_pos + 1);
        else
            cgi_headers_str.erase(status_pos);
    }

    std::string response = "HTTP/1.1 " + http_status + "\r\n";

    if (!cgi_headers_str.empty())
    {
        for (size_t i = 0; i < cgi_headers_str.size(); i++)
        {
            if (cgi_headers_str[i] == '\n' &&
                (i == 0 || cgi_headers_str[i - 1] != '\r'))
                response += '\r';
            response += cgi_headers_str[i];
        }
        if (response.size() >= 2 &&
            !(response[response.size()-2] == '\r' && response[response.size()-1] == '\n'))
            response += "\r\n";
    }

    if (cgi_headers_str.find("Content-Length") == std::string::npos &&
        cgi_headers_str.find("content-length") == std::string::npos)
    {
        std::stringstream len_ss;
        len_ss << cgi_body.size();
        response += "Content-Length: " + len_ss.str() + "\r\n";
    }

    response += "\r\n";

    struct sigaction sa_send_old;
    struct sigaction sa_send_ign;
    sa_send_ign.sa_handler = SIG_IGN;
    sigemptyset(&sa_send_ign.sa_mask);
    sa_send_ign.sa_flags = 0;
    sigaction(SIGPIPE, &sa_send_ign, &sa_send_old);

    std::vector<const char*> parts;
    std::vector<size_t>      part_sizes;
    parts.push_back(response.c_str());   part_sizes.push_back(response.size());
    parts.push_back(cgi_body.c_str());   part_sizes.push_back(cgi_body.size());

    size_t part_idx  = 0;
    size_t part_done = 0;
    size_t total_sent = 0;
    size_t total_size = response.size() + cgi_body.size();
    time_t send_start = time(NULL);

    int client_flags = fcntl(fd, F_GETFL, 0);
    bool restore_nonblock = false;
    if (client_flags >= 0 && (client_flags & O_NONBLOCK))
    {
        if (fcntl(fd, F_SETFL, client_flags & ~O_NONBLOCK) == 0)
            restore_nonblock = true;
    }

    while (part_idx < 2 && time(NULL) - send_start < 60)
    {
        if (part_done >= part_sizes[part_idx])
        {
            part_idx++;
            part_done = 0;
            continue;
        }

        const char* ptr  = parts[part_idx]     + part_done;
        size_t      left = part_sizes[part_idx] - part_done;
        size_t      chunk = left < (size_t)65536 ? left : (size_t)65536;

        ssize_t s = send(fd, ptr, chunk, MSG_NOSIGNAL);
        if (s > 0)
        {
            part_done  += (size_t)s;
            total_sent += (size_t)s;
        }
        else if (s <= 0)
        {
            eraseUser(ConfigPTR->poll_fds);
            break;
        }
    }

    if (restore_nonblock)
        fcntl(fd, F_SETFL, client_flags);

    sigaction(SIGPIPE, &sa_send_old, NULL);

    if (total_sent < total_size)
        std::cerr << "CGI partial send: " << total_sent << "/" << total_size << std::endl;
    else
    std::cout << "\u2192 200 OK (CGI)" << std::endl;
}
