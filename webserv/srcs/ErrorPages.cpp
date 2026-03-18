/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:01:31 by atursun           #+#    #+#             */
/*   Updated: 2026/03/15 16:01:17 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

void ServerConfig::Send403(std::string rootAndPath, int fd)
{
	std::string body;
	std::ifstream error_file(error_pages[403].c_str(), std::ios::binary);
	if (error_file.is_open())
	{
		std::stringstream error_stream;
		error_stream << error_file.rdbuf();
		body = error_stream.str();
		error_file.close();
	}
	else
		body = def_error_pages[403];
	std::stringstream ss;
	ss << body.size();
	std::string http_response =
		"HTTP/1.1 403 Forbidden\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Content-Length: " + ss.str() + "\r\n"
		"\r\n" + body;
	int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
	if (byte_send <= 0)
	{
		std::cerr << "403 send failed to FD: " << fd << std::endl;
		eraseUser(ConfigPTR->poll_fds);
	}
	else
		std::cout << "→ 403 Forbidden: " << rootAndPath << std::endl;
}

void ServerConfig::Send404(std::string rootAndPath, int fd)
{
	std::string body;
	std::ifstream error_file(error_pages[404].c_str(), std::ios::binary);
	if (error_file.is_open())
	{
		std::stringstream error_stream;
		error_stream << error_file.rdbuf();
		body = error_stream.str();
		error_file.close();
	}
	else
		body = def_error_pages[404];
	std::stringstream ss;
	ss << body.size();
	std::string http_response =
		"HTTP/1.1 404 Not Found\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Content-Length: " + ss.str() + "\r\n"
		"\r\n" + body;
	int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
	if (byte_send <= 0)
	{
		std::cerr << "404 send failed to FD: " << fd << std::endl;
		eraseUser(ConfigPTR->poll_fds);
	}
	else
		std::cout << "→ 404 Not Found: " << rootAndPath << std::endl;
}

void ServerConfig::Send405(std::string rootAndPath, int fd)
{
	std::string body;
	std::ifstream error_file(error_pages[405].c_str(), std::ios::binary);
	if (error_file.is_open())
	{
		std::stringstream error_stream;
		error_stream << error_file.rdbuf();
		body = error_stream.str();
		error_file.close();
	}
	else
		body = def_error_pages[405];
	std::stringstream ss;
	ss << body.size();
	std::string http_response =
		"HTTP/1.1 405 Method Not Allowed\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Content-Length: " + ss.str() + "\r\n"
		"\r\n" + body;
	int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
	if (byte_send <= 0)
	{
		std::cerr << "405 send failed to FD: " << fd << std::endl;
		eraseUser(ConfigPTR->poll_fds);
	}
	else
		std::cout << "→ 405 Method Not Allowed: " << rootAndPath  << std::endl;
}

void ServerConfig::Send413(std::string rootAndPath, int fd)
{
	std::string body;
	std::ifstream error_file(error_pages[413].c_str(), std::ios::binary);
	if (error_file.is_open())
	{
		std::stringstream error_stream;
		error_stream << error_file.rdbuf();
		body = error_stream.str();
		error_file.close();
	}
	else
		body = def_error_pages[413];
	std::stringstream ss;
	ss << body.size();
	std::string http_response =
		"HTTP/1.1 413 Payload Too Large\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Content-Length: " + ss.str() + "\r\n"
		"Connection: close\r\n"
		"\r\n" + body;
	int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
	if (byte_send <= 0)
	{
		std::cerr << "413 send failed to FD: " << fd << std::endl;
		eraseUser(ConfigPTR->poll_fds);
	}
	else
		std::cout << "→ 413 Payload Too Large: " << rootAndPath  << std::endl;
}

void ServerConfig::Send500(std::string rootAndPath, int fd)
{
	std::string body;
	std::ifstream error_file(error_pages[500].c_str(), std::ios::binary);
	if (error_file.is_open())
	{
		std::stringstream error_stream;
		error_stream << error_file.rdbuf();
		body = error_stream.str();
		error_file.close();
	}
	else
		body = def_error_pages[500];
	std::stringstream ss;
	ss << body.size();
	std::string http_response =
		"HTTP/1.1 500 Internal Server Error\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Content-Length: " + ss.str() + "\r\n"
		"\r\n" + body;
	int byte_send = send(fd, http_response.c_str(), http_response.size(), MSG_NOSIGNAL);
	if (byte_send <= 0)
	{
		std::cerr << "500 send failed to FD: " << fd << std::endl;
		eraseUser(ConfigPTR->poll_fds);
	}
	else
		std::cout << "→ 500 Internal Server Error: " << rootAndPath << std::endl;
}

