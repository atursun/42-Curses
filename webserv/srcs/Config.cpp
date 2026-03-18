/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:14 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/15 16:43:43 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

Config::Config() {}
Config::~Config() {}

int Config::fileCheck(char *file)
{
    this->configFile.open(file);
    if (!this->configFile.is_open())
    {
        std::cerr << "Cannot open file" << std::endl;
        return (1);
    }
    return (0);
}

const std::vector<ServerConfig> &Config::getServers() const
{
    return Servers;
}

int Config::setupConfig(int i)
{
    ServerConfig *server = &this->Servers[i];
    server->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_fd < 0)
        return (1);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(server->host.c_str());
    addr.sin_port = htons(this->Servers[i].port);
    int opt = 1;
    if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        std::cerr << "setsockopt failed" << std::endl;
        return (1);
    }
    if (bind(server->server_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        std::cerr << "bind failed" << std::endl;
        return (1);
    }
    if (listen(server->server_fd, SOMAXCONN) < 0)
    {
        std::cerr << "listen failed" << std::endl;
        return (1);
    }
    if (fcntl(server->server_fd, F_SETFL, O_NONBLOCK) < 0)
    {
        std::cerr << "fcntl failed" << std::endl;
        return (1);
    }
    struct pollfd pfd;
    pfd.fd = server->server_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    this->poll_fds.push_back(pfd);
    return (0);
}

int Config::new_user_check(int i)
{
    for (size_t j = 0; j < Servers.size(); j++)
    {
        if (poll_fds[i].fd == Servers[j].server_fd)
        {
            struct sockaddr_in client;
            socklen_t client_len = sizeof(client);
            int client_fd = accept(poll_fds[i].fd, (struct sockaddr *)&client, &client_len);
            if (client_fd < 0)
                return (1);
            fcntl(client_fd, F_SETFL, O_NONBLOCK);
            struct pollfd client_pfd;
            client_pfd.fd = client_fd;
            client_pfd.events = POLLIN;
            client_pfd.revents = 0;
            poll_fds.push_back(client_pfd);
            this->client_to_server[client_fd] = &Servers[j];
            this->client_activity_time[client_fd] = time(NULL);
            return (1);
        }
    }
    return (0);
}


static std::string urlDecode(const std::string &str)
{
    std::string decoded;
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == '%')
        {
            if (i + 2 < str.length())
            {
                int value;
                std::stringstream ss;
                ss << std::hex << str.substr(i + 1, 2);
                ss >> value;
                decoded += static_cast<char>(value);
                i += 2;
            }
        }
        else if (str[i] == '+')
            decoded += ' ';
        else
            decoded += str[i];
    }
    return (decoded);
}

void ServerConfig::requested(int fd, LocationConfig &location)
{
    std::string code = location.return_code;
    if (code != "301" && code != "302" && code != "303" && code != "307" && code != "308")
        code = "302";

    
    std::string response = "HTTP/1.1 " + code;
    response += " Moved Permanently\r\n";
    response += "Location: " + location.return_url + "\r\n";
    response += "Content-Length: 0\r\n";
    response += "Connection: close\r\n\r\n";
    if (send(fd, response.c_str(), response.size(), 0) <= 0)
    {
        std::cerr << "send failed to FD: " << fd << std::endl;
        eraseUser(ConfigPTR->poll_fds);
        return;
    }
    std::cout << "→ " << code << " Redirect: " << location.return_url << std::endl;
}

void ServerConfig::eraseUser(std::vector<struct pollfd> &poll_fds)
{
    close(poll_fds[index].fd);
    poll_fds.erase(poll_fds.begin() + index);
    index--;
}


static std::string dechunkBody(const std::string &chunked_body)
{
    std::string result;
    size_t pos = 0;

    
    while (pos < chunked_body.size())
    {
        
        size_t line_end = chunked_body.find("\r\n", pos);
        if (line_end == std::string::npos)
            line_end = chunked_body.find("\n", pos);
        if (line_end == std::string::npos)
            break;

        std::string size_str = chunked_body.substr(pos, line_end - pos);
        int chunk_size;
        std::stringstream ss;
        ss << std::hex << size_str;
        ss >> chunk_size;

        
        if (chunk_size == 0)
            break;

        
        pos = line_end;
        if (chunked_body[pos] == '\r')
            pos++;
        if (pos < chunked_body.size() && chunked_body[pos] == '\n')
            pos++;

        
        if (pos + chunk_size <= chunked_body.size())
            result.append(chunked_body.substr(pos, chunk_size));

        
        pos += chunk_size;
        if (pos < chunked_body.size() && chunked_body[pos] == '\r')
            pos++;
        if (pos < chunked_body.size() && chunked_body[pos] == '\n')
            pos++;
    }
    return result;
}

bool ServerConfig::request_check(std::string &raw_request)
{
    size_t header_end = raw_request.find("\r\n\r\n");
    bool is_crlf = (header_end != std::string::npos);

    if (!is_crlf)
    {
        header_end = raw_request.find("\n\n");
        if (header_end == std::string::npos)
            return false; 
    }

    
    const char *data = raw_request.data();
    size_t header_size = header_end; 
    std::string header(data, header_size);

    
    if (header.find("Transfer-Encoding:") != std::string::npos)
    {
        
        size_t check_from = raw_request.size() > 16 ? raw_request.size() - 16 : 0;
        if (raw_request.find("0\r\n\r\n", check_from) != std::string::npos)
        {
            std::cerr << "\033[2K\r[BODY] Chunked complete! " << raw_request.size() << " bytes" << std::endl;
            return true;
        }
        std::cerr << "\033[2K\r[BODY] Waiting chunked... " << raw_request.size() << " bytes" << std::flush;
        return false;
    }

    
    size_t cl_pos = header.find("Content-Length:");
    if (cl_pos != std::string::npos)
    {
        cl_pos += 15;
        while (cl_pos < header.size() && (header[cl_pos] == ' ' || header[cl_pos] == '\t'))
            cl_pos++;
        size_t num_end = header.find(is_crlf ? "\r\n" : "\n", cl_pos);
        std::stringstream ss(std::string(header.substr(cl_pos, num_end - cl_pos)));
        long long content_lenght = 0;
        ss >> content_lenght;

        if (content_lenght > 0 && (size_t)content_lenght > client_max_body_size)
            return true;

        
        long long current_lenght = (long long)raw_request.size() - (long long)(header_end + (is_crlf ? 4 : 2));
        if (current_lenght < content_lenght)
        {
            std::cerr << "\033[2K\r[BODY] " << current_lenght << "/" << content_lenght << " bytes" << std::flush;
            return false;
        }
        std::cerr << "\033[2K\r[BODY] Complete! " << content_lenght << "/" << content_lenght << " bytes" << std::endl;
    }

    
    if (header.find("/favicon.ico") != std::string::npos || header.find(".well-known") != std::string::npos)
        return false;
    if (raw_request.size() > client_max_body_size)
        return false;

    return true;
}


void ServerConfig::read_data(std::vector<struct pollfd> &poll_fds, int &i)
{
    index = i;
    char buffer[65536]; 
    int byt_reads;
    int fd = poll_fds[i].fd;

    if (poll_fds[i].revents & POLLIN)
    {
        byt_reads = recv(poll_fds[i].fd, buffer, sizeof(buffer) - 1, 0); 

        if (byt_reads <= 0)
        {
            client_buffers.erase(poll_fds[i].fd);
            eraseUser(poll_fds);
            return;
        }
        client_buffers[fd].append(buffer, byt_reads);

        if (!request_check(client_buffers[fd]))
            return;
        poll_fds[i].events = POLLOUT;
    }
    else if (poll_fds[i].revents & POLLOUT)
    {

        std::string raw_request = client_buffers[fd];
        client_buffers.erase(poll_fds[i].fd);
        bool is_crlf = (raw_request.find("\r\n\r\n") != std::string::npos);
        const std::string header_sep = is_crlf ? "\r\n\r\n" : "\n\n";
        const std::string line_sep = is_crlf ? "\r\n" : "\n";
        
        if (raw_request.find("Transfer-Encoding:") != std::string::npos)
        {
            
            size_t header_end = raw_request.find(header_sep);
            if (header_end == std::string::npos)
                header_end = raw_request.find("\n\n");

            if (header_end != std::string::npos)
            {
                std::string header = raw_request.substr(0, header_end + header_sep.size());
                std::string chunked_body = raw_request.substr(header_end + header_sep.size());
                std::string dechunked_body = dechunkBody(chunked_body);

                
                size_t te_pos = header.find("Transfer-Encoding:");
                if (te_pos != std::string::npos)
                {
                    size_t te_end = header.find(line_sep, te_pos);
                    header.erase(te_pos, te_end - te_pos + line_sep.size());
                }

                
                std::stringstream ss;
                ss << dechunked_body.size();
                size_t insert_pos = header.find(header_sep);
                header.insert(insert_pos, "Content-Length: " + ss.str() + line_sep);

                raw_request = header + dechunked_body;
            }
        }

        
        if (raw_request.size() > client_max_body_size)
        {
            client_buffers.erase(poll_fds[i].fd);
            Send413("", fd);
            poll_fds[i].events = POLLIN;
            return;
        }

        

        size_t first_space = raw_request.find(" ");
        if (first_space == std::string::npos)
        {
            poll_fds[i].events = POLLIN;
            return; 
        }

        std::string method = raw_request.substr(0, first_space);

        
        size_t path_start = raw_request.find(" ") + 1;
        size_t path_end = raw_request.find(" ", path_start);
        std::string request_path = raw_request.substr(path_start, path_end - path_start);
        request_path = urlDecode(request_path);
        std::cout << "------------\n"
                  << method << " " << request_path << std::endl;
        if (method != "GET" && method != "POST" && method != "DELETE")
        {
            Send405(request_path, fd);
            poll_fds[i].events = POLLIN;
            return;
        }

        {
            std::string clean_req_path = request_path;
            size_t qp = request_path.find('?');
            if (qp != std::string::npos)
                clean_req_path = request_path.substr(0, qp);
            LocationConfig *loc = findMatchingLocation(clean_req_path);
            if (loc && loc->client_max_body_size > 0)
            {
           
                size_t body_sz = 0;
                size_t cl_hdr = raw_request.find("Content-Length:");
                if (cl_hdr != std::string::npos)
                {
                    cl_hdr += 15;
                    while (cl_hdr < raw_request.size() &&
                           (raw_request[cl_hdr] == ' ' || raw_request[cl_hdr] == '\t'))
                        cl_hdr++;
                    size_t cl_end = raw_request.find("\r\n", cl_hdr);
                    if (cl_end == std::string::npos)
                        cl_end = raw_request.find("\n", cl_hdr);
                    std::string cl_str = raw_request.substr(cl_hdr,
                                                            cl_end != std::string::npos ? cl_end - cl_hdr : std::string::npos);
                    std::stringstream cl_ss(cl_str);
                    cl_ss >> body_sz;
                }
                else
                {
                    size_t hend = raw_request.find("\r\n\r\n");
                    if (hend != std::string::npos)
                        body_sz = raw_request.size() > hend + 4 ? raw_request.size() - hend - 4 : 0;
                }
                if (body_sz > loc->client_max_body_size)
                {
                    client_buffers.erase(poll_fds[i].fd);
                    Send413(request_path, fd);
                    poll_fds[i].events = POLLIN;
                    return;
                }
            }
        }

        if (check_is_method_allowed(request_path, method, poll_fds[i].fd) == true && (method == "POST" || method == "DELETE"))
        {
            if (method == "POST")
                handle_post(raw_request, request_path, poll_fds[i].fd);
            if (method == "DELETE")
                handle_delete(request_path, poll_fds[i].fd);
            poll_fds[i].events = POLLIN;
            return;
        }
        std::string rootAndPath(root);
        rootAndPath += request_path;
        for (size_t j = 0; j < locations.size(); j++) 
        {
            if (locations[j].path == request_path && locations[j].IsReturn)
            {
                requested(poll_fds[i].fd, locations[j]);
                poll_fds[i].events = POLLIN;
                return;
            }
        }
        if (check_is_method_allowed(request_path, method, poll_fds[i].fd))
        {
            handle_get(raw_request, request_path, poll_fds[i].fd, findMatchingLocation(request_path));
            poll_fds[i].events = POLLIN;
            return;
        }
        poll_fds[i].events = POLLIN;
    }
}

void Config::inactive_client_check()
{
    time_t now = time(NULL);
    
    for (int i = 0; i < (int)poll_fds.size(); i++)
    {
        int fd = poll_fds[i].fd;

        
        bool is_server_socket = false;
        for (size_t j = 0; j < Servers.size(); j++)
        {
            if (fd == Servers[j].server_fd)
            {
                is_server_socket = true;
                break;
            }
        }
        if (is_server_socket)
            continue;

        
        if (client_activity_time.find(fd) != client_activity_time.end())
        {
            if (now - client_activity_time[fd] > CLIENT_TIMEOUT)
            {
                close(fd);
                client_to_server.erase(fd);
                client_activity_time.erase(fd);
                poll_fds.erase(poll_fds.begin() + i);
                i--; 
            }
        }
    }
}

void Config::startServer()
{
    int answer;
    std::cout << "Server starting" << std::endl;
    poll_fds.reserve(4096);
    while (1)
    {
        answer = poll(&this->poll_fds[0], poll_fds.size(), 1000);
        if (answer < 0 || g_signal == 0)
            break;
        if (answer == 0)
        {
            inactive_client_check();
            continue;
        }
        for (int i = 0; i < (int)poll_fds.size(); i++)
        {
            if (poll_fds[i].revents == 0)
                continue;
            if (poll_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
            {
                int bad_fd = poll_fds[i].fd;
                std::map<int, ServerConfig*>::iterator it = client_to_server.find(bad_fd);
                if (it != client_to_server.end() && it->second)
                    it->second->client_buffers.erase(bad_fd);
                client_to_server.erase(bad_fd);
                client_activity_time.erase(bad_fd);
                close(bad_fd);
                poll_fds.erase(poll_fds.begin() + i);
                i--;
                continue;
            }
            if (new_user_check(i))
                continue;
            else
            {
                int client_fd = poll_fds[i].fd;
                if (client_to_server.find(client_fd) != client_to_server.end())
                {
                    client_activity_time[client_fd] = time(NULL);
                    client_to_server[client_fd]->read_data(poll_fds, i);
                    i = client_to_server[client_fd]->index;
                }
                else
                {
                    close(client_fd);
                    poll_fds.erase(poll_fds.begin() + i);
                    i--;
                }
            }
        }
    }
}
