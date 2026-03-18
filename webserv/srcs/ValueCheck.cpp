/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ValueCheck.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:06:14 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/13 15:06:15 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

int Config::listenCheck(std::stringstream &ss, ServerConfig &server)
{
	std::string value;
	std::string PortStr;
	int port;
	size_t colonPos;

	value = getValue(ss);
	colonPos = value.find(':');
	if (colonPos == std::string::npos)
	{
		port = std::atoi(value.c_str());
		if (value.find_first_not_of("1234567890") != std::string::npos) 
		{
			std::cerr << "Port number invalid " << value << std::endl;
			return (0);
		}
	}
	else
	{
		server.host = value.substr(0, colonPos);
		if (hostCheck(server.host))
			return (0);
		PortStr = value.substr(colonPos + 1);
		port = std::atoi(PortStr.c_str());
	}
	if (PortStr.size() > 6 || port < 0 || port > 65535 || PortStr.find_first_not_of(":1234567890") != std::string::npos)
	{
		std::cerr << "Port number is not valid : " << PortStr <<  std::endl;
		return (0);
	}
	server.port = port;
	return (1);
}

int hostCheck(std::string &str)
{
	int segmentCount = 0;
	size_t pos = str.find_first_not_of("0123456789.");
	if (pos != std::string::npos)
	{
		std::cerr << "Invalid host : " << str << std::endl;
		return(1);
	}
	std::stringstream ss(str);
	std::string value;
	while (std::getline(ss, value, '.'))
	{
		if (value.empty())
		{
			std::cerr << "invalid host " << str << std::endl;
			return (1);
		}
		if (value.find_first_not_of("1234567890") != std::string::npos)
		{
			std::cerr << "Invalid host " << str << std::endl;
			return (1);
		}
		int number = std::atoi(value.c_str());
		if (number < 0 || number > 255)
		{
			std::cerr << "Invalid host " << str << std::endl;
			return (1);
		}
		segmentCount++;
	}	
	if (segmentCount != 4)
	{
		std::cerr << "Invalid host " << str <<  std::endl; 
		return (1);
	}
	return (0);
}

std::pair<int, std::string> errorPage(std::stringstream &ss, ServerConfig &server)
{
	std::map<int, std::string> Errors;
	std::string errorPage;
	int			errorNumber;
	std::string buffer;
	ss >> errorNumber;
	if (ss.fail())
	{
		std::cerr << "Error number is not valid" << std::endl;
		return (std::make_pair(0, ""));
	}
	ss >> errorPage;
	if (!errorPage.empty() && errorPage[errorPage.length() - 1] == ';')
        errorPage.resize(errorPage.size() - 1);

	size_t dot = errorPage.find('.');
	if (dot == std::string::npos)
		return (std::make_pair(0, ""));
	
	std::string extansionCheck = errorPage.substr(dot);
	if (extansionCheck != ".html")
	{
		std::cerr << errorNumber << " error page extansion not valid" << std::endl;
		return (std::make_pair(0, ""));
	}
	errorPage =  (!server.root.empty() ? server.root : ".") + errorPage;
	return (std::make_pair(errorNumber, errorPage));
}

