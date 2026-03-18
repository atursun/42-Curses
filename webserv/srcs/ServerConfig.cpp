/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:38 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/14 14:38:46 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerConfig.hpp"

ServerConfig::ServerConfig() 
{
    this->port = -1;
    this->host = "";
    this->server_name = "";
    this->client_max_body_size = 70547387968;
    this->root = "";
    this->error_pages.insert(std::make_pair(403,""));
    this->error_pages.insert(std::make_pair(404,""));
    this->error_pages.insert(std::make_pair(405,""));
    this->error_pages.insert(std::make_pair(413,""));
    this->error_pages.insert(std::make_pair(500,""));
    this->def_error_pages.insert(std::make_pair(403,"<html><head><title>403 Forbidden</title></head><body style=\"text-align:center;font-family:sans-serif\"><h1>403 Forbidden</h1><p>Access invalid.</p></body></html>"));
    this->def_error_pages.insert(std::make_pair(404,"<html><head><title>404 Not Found</title></head><body style=\"text-align:center;font-family:sans-serif\"><h1>404 Not Found</h1><p>The requested resource could not be found.</p></body></html>"));
    this->def_error_pages.insert(std::make_pair(405,"<html><head><title>405 Method Not Allowed</title></head><body style=\"text-align:center;font-family:sans-serif\"><h1>405 Method Not Allowed</h1><p>Method not allowed.</p></body></html>"));
    this->def_error_pages.insert(std::make_pair(413,"<html><head><title>413 Payload Too Large</title></head><body style=\"text-align:center;font-family:sans-serif\"><h1>413 Payload Too Large</h1><p>Request body too large.</p></body></html>"));
    this->def_error_pages.insert(std::make_pair(500,"<html><head><title>500 Internal Server Error</title></head><body style=\"text-align:center;font-family:sans-serif\"><h1>500 Internal Server Error</h1><p>Server error.</p></body></html>"));
}
