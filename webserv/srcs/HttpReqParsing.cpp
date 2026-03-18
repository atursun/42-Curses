/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpReqParsing.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:05:33 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/15 16:44:37 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/ParsingHttp.hpp"


static std::string resolveFilePath(const std::string& request_path, LocationConfig* location, const std::string& server_root)
{
    if (!location)
        return server_root + request_path;

    if (!location->path.empty() && location->path[0] == '.')
        return server_root + request_path;

    std::string path_after = request_path;
    std::string loc_path = location->path;

    if (loc_path != "/" && !loc_path.empty() && loc_path[loc_path.size() - 1] == '/')
        loc_path = loc_path.substr(0, loc_path.size() - 1);
    if (path_after != "/" && !path_after.empty() && path_after[path_after.size() - 1] == '/')
        path_after = path_after.substr(0, path_after.size() - 1);

    if (path_after.find(loc_path) == 0)
        path_after = path_after.substr(loc_path.length());

    if (!path_after.empty() && path_after[0] != '/')
        path_after = "/" + path_after;

    std::string base = location->root.empty() ? server_root : location->root;
    return base + path_after;
}

void    ServerConfig::handle_post(std::string raw_request, std::string request_path, int fd)
 {
    LocationConfig* cgi_loc = findCgiLocation(request_path);
    if (cgi_loc && isMethodAllowed(cgi_loc, "POST"))
    {
        LocationConfig* path_loc = findMatchingLocation(request_path);
        std::string file_path = resolveFilePath(request_path, path_loc, root);
        handle_cgi(raw_request, request_path, file_path, cgi_loc, "POST", fd);
        return;
    }

    std::string body;
    std::string http_response;
	size_t body_pos = raw_request.find("\r\n\r\n");     

    
    if (body_pos != std::string::npos)
    {
        std::string request_body = raw_request.substr(body_pos + 4);

        
        if (raw_request.find("Content-Type: multipart/form-data") != std::string::npos)
        {
            
            size_t boundary_pos = raw_request.find("boundary=");
            if (boundary_pos != std::string::npos)
            {
                boundary_pos += 9; 
                size_t boundary_end = raw_request.find("\r\n", boundary_pos);
                std::string boundary = raw_request.substr(boundary_pos, boundary_end - boundary_pos);
                
                
                size_t filename_pos = request_body.find("filename=\"");
                if (filename_pos != std::string::npos)
                {
                    filename_pos += 10; 
                    size_t filename_end = request_body.find("\"", filename_pos);
                    std::string filename = request_body.substr(filename_pos, filename_end - filename_pos);
                    
                    
                    size_t content_start = request_body.find("\r\n\r\n", filename_end);
                    if (content_start != std::string::npos)
                    {
                        content_start += 4;
                        
                        size_t content_end = request_body.find("\r\n--" + boundary, content_start);
                        if (content_end == std::string::npos)
                            content_end = request_body.find("--" + boundary + "--", content_start);
                        if (content_end == std::string::npos)
                        {
                            std::cerr << "ERROR" << std::endl;
                            return;
                        }
                        size_t content_length = content_end - content_start;

                        
                        std::string upload_path = "./www" + request_path + "/" + filename;
                        std::ofstream outfile(upload_path.c_str(), std::ios::binary);
                        if (outfile.is_open())
                        {
                            outfile.write(request_body.data() + content_start, content_length);
                            outfile.close();
                            
                            body = "<html><body><h1>Upload Successful</h1><p>File: " + filename + " uploaded successfully!</p></body></html>";
                        }
                        else
                        {
                            Send500(upload_path, fd);
                            return;
                        }
                    }
                }
            }
        }
        else
        {
            body = "<html><body><h1>POST Received</h1><p>Data received successfully!</p></body></html>";
        }
    }
    
    std::stringstream ss;
    ss << body.size();
    
    http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: " + ss.str() + "\r\n"
        "\r\n" + body;
        
    int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
    if (byte_send <= 0)
    {
        std::cerr << "POST send failed to FD: " << fd << std::endl;
        eraseUser(ConfigPTR->poll_fds);
    }
    else
        std::cout << "\u2192 200 OK" << std::endl;
}

void    ServerConfig::handle_delete(std::string request_path, int fd)
{
    std::string body;
    std::string http_response;
    std::string file_path = root + request_path;

    std::string parent_dir = file_path.substr(0, file_path.find_last_of('/'));
    if (access(parent_dir.c_str(), W_OK) != 0)
        Send403(file_path ,fd);

    
    if (access(file_path.c_str(), F_OK) != 0)
    {
        Send404(file_path ,fd);
        return;
    }

    
    if (remove(file_path.c_str()) == 0)
    {
        body = "<html><body><h1>Delete Successful</h1><p>File deleted successfully: " + request_path + "</p></body></html>";
        std::stringstream ss;
        ss << body.size();
        
        http_response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf-8\r\n"
            "Content-Length: " + ss.str() + "\r\n"
            "\r\n" + body;
    }
    else
    {
        Send500(file_path ,fd);
        return;
    }
    int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
    if (byte_send <= 0)
    {
        std::cerr << "DELETE send failed to FD: " << fd << std::endl;
        eraseUser(ConfigPTR->poll_fds);
    }
    else
        std::cout << "\u2192 200 OK" << std::endl;
}

void    ServerConfig::handle_file(std::string body, std::string file_path, int fd)
{
    std::string content_type = "text/html; charset=utf-8";

    std::stringstream file_stream;
    std::ifstream new_file(file_path.c_str());
    file_stream << new_file.rdbuf();
    body = file_stream.str();
    new_file.close();

    if (file_path.find(".html") != std::string::npos)
        content_type = "text/html; charset=utf-8";
    else if (file_path.find(".css") != std::string::npos)
        content_type = "text/css";
    else if (file_path.find(".js") != std::string::npos)
        content_type = "application/javascript";
    else if (file_path.find(".jpg") != std::string::npos || file_path.find(".jpeg") != std::string::npos)
        content_type = "image/jpeg";
    else if (file_path.find(".png") != std::string::npos)
        content_type = "image/png";
    else if (file_path.find(".txt") != std::string::npos)
        content_type = "text/plain; charset=utf-8";
    else if (file_path.find(".md") != std::string::npos)
        content_type = "text/markdown; charset=utf-8";
    else if (file_path.find(".pdf") != std::string::npos)
        content_type = "application/pdf";

    std::stringstream ss;
    ss << body.size();

    std::string http_response = 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: " + content_type + "\r\n"
        "Content-Length: " + ss.str() + "\r\n"
        "\r\n" + body;

    int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
    if (byte_send <= 0)
    {
        std::cerr << "GET send failed to FD: " << fd << std::endl;
        eraseUser(ConfigPTR->poll_fds);   
    }
    else
        std::cout << "\u2192 200 OK" << std::endl;

}

std::string directory_listing(std::string file_path, std::string request_path) {

    DIR* dir = opendir(request_path.c_str());
    if (!dir)
        return (""); 

    struct dirent* entry;
    std::stringstream html;

    
    html << "<html>\n";
    html << "<head><title>Index of " << file_path << "</title></head>\n";
    html << "<body>\n";
    html << "<h1>Index of " << file_path << "</h1>\n";
    html << "<ul>\n";
    
    while ((entry = readdir(dir)) != NULL)
    {
        std::string name = entry->d_name;

        html << "<li><a href=\"" << file_path;
        if (file_path[file_path.size() - 1] != '/')
            html << "/";

        html << name << "\">"
             << name
             << "</a></li>\n";
    }
    html << "</ul>\n";
    html << "</body>\n";
    html << "</html>\n";
    return (closedir(dir), html.str());
}

void    ServerConfig::handle_get(std::string raw_request, std::string request_path, int fd, LocationConfig *location)
{
    std::string clean_path = request_path;
    size_t qs_pos = request_path.find('?');
    if (qs_pos != std::string::npos)
        clean_path = request_path.substr(0, qs_pos);

    
    std::string path_after_location = clean_path;
    std::string location_path = location->path;
    
    
    if (location_path != "/" && !location_path.empty() && location_path[location_path.size() - 1] == '/')
        location_path = location_path.substr(0, location_path.size() - 1);
    if (path_after_location != "/" && !path_after_location.empty() && path_after_location[path_after_location.size() - 1] == '/')
        path_after_location = path_after_location.substr(0, path_after_location.size() - 1);
    
    
    if (path_after_location.find(location_path) == 0)
        path_after_location = path_after_location.substr(location_path.length());
    
    
    if (!path_after_location.empty() && path_after_location[0] != '/')
        path_after_location = "/" + path_after_location;
    
    
    std::string file_path = location->root + path_after_location;

    {
        LocationConfig* cgi_loc = findCgiLocation(clean_path);
        if (cgi_loc && isMethodAllowed(cgi_loc, "GET"))
        {
            handle_cgi(raw_request, request_path, file_path, cgi_loc, "GET", fd);
            return;
        }
    }

    
    std::ifstream file(file_path.c_str(), std::ios::binary);
    std::string body;

    
    DIR* dir = opendir(file_path.c_str());
    if (dir != NULL)
    {
        closedir(dir);
        
        if (!location->index.empty()) 
        {
            std::string index_path = file_path;
            if (index_path[index_path.size() - 1] != '/')
                index_path += "/";
            index_path += location->index;
            
            std::ifstream index_file(index_path.c_str());
            if (index_file.good())
            {
                index_file.close();
                file_path = index_path;
                
                std::string new_req_path = clean_path;
                if (!new_req_path.empty() && new_req_path[new_req_path.size() - 1] != '/')
                    new_req_path += "/";
                new_req_path += location->index;

                LocationConfig* cgi_loc = findCgiLocation(new_req_path);
                if (cgi_loc && isMethodAllowed(cgi_loc, "GET"))
                {
                    if (qs_pos != std::string::npos)
                        new_req_path += request_path.substr(qs_pos);
                    handle_cgi(raw_request, new_req_path, file_path, cgi_loc, "GET", fd);
                    return;
                }
                
                handle_file(body, file_path, fd);
                return;
            }
            else
            {
                index_file.close();
                if (request_path[request_path.size() - 1] != '/')
                {
                    Send404(file_path, fd);
                    return;
                }
                
                if (location->autoindex)
                {
                    std::string listing = directory_listing(request_path, file_path);
                    if (listing.empty())
                        Send403(file_path, fd);
                    else
                    {
                        std::stringstream ss;
                        ss << listing.size();
                        std::string http_response =
                            "HTTP/1.1 200 OK\r\n"
                            "Content-Type: text/html; charset=utf-8\r\n"
                            "Content-Length: " + ss.str() + "\r\n"
                            "\r\n" + listing;
                        if (send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL) <= 0)
                        {
                            eraseUser(ConfigPTR->poll_fds);
                            return;
                        }
                    }
                    return;
                }
                else
                {
                    Send403(file_path, fd);
                    return;
                }
            }
        } 
        else
        {
            if (location->autoindex)
            {
                std::string listing = directory_listing(request_path, file_path);
                if (listing.empty())
                    Send403(file_path, fd);
                else
                {
                    std::stringstream ss;
                    ss << listing.size();
                    std::string http_response =
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=utf-8\r\n"
                        "Content-Length: " + ss.str() + "\r\n"
                        "\r\n" + listing;
                    if (send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL) <= 0)
                    {
                        eraseUser(ConfigPTR->poll_fds);
                        return;
                    }

                }
                return;
            }
            else
            {
                Send403(file_path, fd);
                return;
            }
        }
    }
    if (file.is_open())
		handle_file(body, file_path, fd);
	else
		Send404(file_path, fd);
    return;
}





bool isMethodAllowed(LocationConfig* location, const std::string& method) {
    if (location == NULL)
        return (true); 
    if (location->allowed_methods.empty())
        return (true); 
    
    for (size_t i = 0; i < location->allowed_methods.size(); i++)
    {
        if (location->allowed_methods[i] == method)
            return (true);  
    }
    return (false); 
}



LocationConfig* ServerConfig::findMatchingLocation(const std::string& request_path)
{
    LocationConfig* best_match = NULL;
    size_t best_match_length = 0;

    
    std::string normalized_request = request_path;
    if (normalized_request != "/" && !normalized_request.empty() && normalized_request[normalized_request.size() - 1] == '/')
        normalized_request = normalized_request.substr(0, normalized_request.size() - 1);

    for (size_t i = 0; i < locations.size(); i++)
    {
        
        std::string location_path = locations[i].path;
        if (location_path != "/" && !location_path.empty() && location_path[location_path.size() - 1] == '/')
            location_path = location_path.substr(0, location_path.size() - 1);
                
        
        if (normalized_request.find(location_path) == 0)
        {
            
            if (location_path.length() > best_match_length)
            {
                best_match = &locations[i];
                best_match_length = location_path.length();
            }
        }
    }
    return (best_match);
}


bool    ServerConfig::check_is_method_allowed(std::string request_path, std::string method, int i) {
    
    
    LocationConfig* location = findMatchingLocation(request_path);

    if (!isMethodAllowed(location, method))
    {
        return (Send405(request_path, i), false);
    }
    return (true);
}
