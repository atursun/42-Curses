/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:31 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/15 16:45:25 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCONFIG_HPP
# define SERVERCONFIG_HPP

#include "LocationConfig.hpp"
#include <map>
#include <vector>
#include <string>

class Config;

class ServerConfig {
public:
    std::map<int, std::string> client_buffers;     
    int                         port;             
    std::string                 host;             
    std::string                 server_name;      
    unsigned long               client_max_body_size; 
    int                         server_fd;
    std::map<int, std::string>  error_pages;
    std::map<int, std::string>  def_error_pages;
    std::string                 root;
    std::vector<LocationConfig> locations;
    int                         index;
    Config                      *ConfigPTR;

    ServerConfig();
    void	eraseUser(std::vector<struct pollfd>  &poll_fds);
    void    Send403(std::string rootAndPath, int fd);
    void    Send404(std::string rootAndPath, int fd);
    void    Send405(std::string rootAndPath, int fd);
    void    Send500(std::string rootAndPath, int fd);
    void    Send413(std::string rootAndPath, int fd);
    void    requested(int fd, LocationConfig &location);
    void    read_data(std::vector<struct pollfd>  &poll_fds, int &i);
    void    handle_get(std::string raw_request, std::string request_path, int fd, LocationConfig *location);
    void    handle_post(std::string raw_request, std::string request_path, int fd);
    void    handle_delete(std::string request_path, int fd);
    void    handle_file(std::string body, std::string file_path, int fd);
    void    handle_cgi(std::string raw_request, std::string request_path,
                       std::string file_path, LocationConfig* cgi_loc,
                       std::string method, int fd);
    LocationConfig* findCgiLocation(const std::string& request_path);



    bool    check_is_method_allowed(std::string request_path, std::string method, int i);
    bool    request_check(std::string &raw_request);
    LocationConfig* findMatchingLocation(const std::string& request_path);

};




#endif