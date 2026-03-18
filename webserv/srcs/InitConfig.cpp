/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitConfig.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:05:58 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/14 14:44:11 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

int	Config::configLocationWordCheck(std::stringstream &ss, std::string word, LocationConfig &location)
{
	if (word == "root")
		location.root = getValue(ss);
	else if (word == "allow_methods")
	{
		while (ss >> word)
		{
			std::string method = word;
			if (method[method.size() -1 ] == ';')
			{
				method.resize(method.size() -1);
				location.allowed_methods.push_back(method);
				break;
			}
			location.allowed_methods.push_back(method);
		}
	}
	else if (word == "upload_path")
		location.upload_path = getValue(ss);
	else if (word == "autoindex")
	{
		std::string value = getValue(ss);
		if (value == "on")
			location.autoindex = true;
		else if (value != "off")
		{
			std::cerr << "autoindex not valid : " << value << std::endl;
			return (1);
		}
	}
	else if (word == "index")
		location.index = getValue(ss);
	else if (word == "cgi_path")
		location.cgi_path = getValue(ss);
	else if (word == "cgi_ext")
		location.cgi_ext = getValue(ss);
	else if (word == "client_max_body_size")
	{
		std::string sizeStr = getValue(ss);
		if (sizeStr.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cerr << "client_max_body_size not valid : " << sizeStr << std::endl;
			return (1);
		}
		location.client_max_body_size = std::atol(sizeStr.c_str());
	}
	else if (word == "return")
	{
		location.return_code = getValue(ss);
		location.return_url = getValue(ss);
		location.IsReturn = true;
	}
	else
	{
		std::cerr << "Unknown config : " << word << std::endl;
		return (1);
	}
	return (0);
}


int	Config::SetLocation(std::string &localLine, ServerConfig &server)
{
	LocationConfig		location;
	std::stringstream	ss(localLine);
	std::string			line;
	std::string			word;
	int					scope = 2;
	std::string			scopeCheck;

	ss >> word;
	ss >> word;
	if (word == "{")
	{
		std::cerr << "Path not found" << std::endl;
		return (1);
	}
	location.path = word;
	ss >> word;
	if (word == "{")
		scope = true;
 	if (ss >> word && word[0] != '#')
	{
		std::cerr << "Invalid syntax after location block start: " << word << std::endl;
		return (1);
	}	
	while (getline(configFile, line))
	{
		ss.clear();
		ss.str(line);
		if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos)
			continue;
		ss >> word;
		scopeCheck = ScopeAndHashCheck(word, scope, ss);
		if (scopeCheck == "continue")
			continue;
		if (scopeCheck == "break")
			break;
		if (scopeCheck == "fail")
			return (1);
		if (line[line.size() - 1] != ';' && line.find("location") == std::string::npos)
		{
			std::cerr << "error: expected ';' after expression" << std::endl;
			return (1);
		}
		if (configLocationWordCheck(ss, word, location))
			return (1);
	}
	if (scope == 2 || scope == true)
	{
		std::cerr << "Location scope error" << std::endl;
		return (1);
	}
	server.locations.push_back(location);
	return (0);
}

int	Config::configWordCheck(std::stringstream &ss, std::string word, ServerConfig &server, std::string &line)
{
	if (word == "listen")
	{
		if (!listenCheck(ss, server))
			return (1);
	}
	else if (word == "server_name")
		server.server_name = getValue(ss);
	else if (word == "root")
		server.root = getValue(ss);
	else if (word == "host")
	{
		server.host = getValue(ss);
		if (hostCheck(server.host))
			return (1);
	}
	else if (word == "error_page")
	{
		std::pair<int, std::string> errors = errorPage(ss, server);
		if (errors.first == 0 && errors.second == "")
			return (1);
		if (server.error_pages.find(errors.first) != server.error_pages.end())
		{
			server.error_pages.erase(server.error_pages.find(errors.first));
			server.error_pages.insert(errors);
		}
	}
	else if (word == "client_max_body_size")
	{
		std::string sizeStr = getValue(ss);
		if (sizeStr.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cerr  << "client max body size not valid : " << sizeStr << std::endl;
			return (1);
		}
		server.client_max_body_size = std::atol(sizeStr.c_str());
	}
	else if (word == "location")
	{
		if (SetLocation(line, server))
			return (1);
		if (LocationCheck(server.locations.back()))
			return (1);
	}
	else
	{
		std::cerr << "Unknown config " << word << std::endl;
		return (1);
	}
	return (0);
}

int	Config::initConfig()
{
	std::string line;
	std::stringstream ss;
	std::string word;
	std::string value;
	int			scope = 2;
	std::string scopeCheck;

	while (getline(configFile, line))
	{
		if (line.empty())
			continue;
		ss.clear();
		ss.str(line);
		ss >> word;
		if (word == "server")
		{
			scope = 2;
			ServerConfig server;
			server.ConfigPTR = this;
			if (ss >> word && (word[0] != '#' && word[0] != '{'))
			{
				std::cerr << "Invalid syntax after location block start: " << word << std::endl;
				return (1);
			}
			if (word == "{")
				scope = true;
			while (getline(configFile, line))
			{
				if (line.empty() || !strIsSpaceCheck(line))
					continue;
				ss.clear();
				ss.str(line);
				ss >> word;
				scopeCheck = ScopeAndHashCheck(word, scope, ss);
				if (scopeCheck == "continue")
					continue;
				if (scopeCheck == "break")
					break;
				if (scopeCheck == "fail")
					return (1);
				if (line[line.size() - 1] != ';' && word != "location")
				{
					std::cerr << "error: expected ';' after expression" << std::endl;
					return (1);
				}
				if (configWordCheck(ss, word, server, line))
					return (1);
			}
			if (server.port == -1)
			{
				std::cerr << "Port number is missing" << std::endl;
				return (1);
			}
			if (scope == 2 || scope == true)
			{
				std::cerr << "Scope error" << std::endl;
				return (1);
			}
			this->Servers.push_back(server);
		}
		else if (word[0] != '#')
		{
			std::cerr << "Invalid config : " << word << std::endl;
			return (1);
		}
	}
	if (Servers.empty())
	{
		std::cerr << "Server not found " << std::endl;
		return (1);
	}
	return (0);
}

