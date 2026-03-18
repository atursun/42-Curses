/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CheckLocation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:06:21 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/13 15:06:22 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

int	IndexHtmlCheck(LocationConfig &location)
{
	if (location.root.empty())
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	std::string IndexFullpath;
	IndexFullpath = location.root + "/" + location.index;
	int fd = open(IndexFullpath.c_str(), O_RDONLY);
	if (fd == -1)
	{
        std::cerr << "Warning: Index file not found at startup: " << IndexFullpath <<  std::endl;
		return (1);
	}
	return (0);
}

int LocationCheck(LocationConfig &location)
{
	if (!location.root.empty() && dirCheck(location.root))
	{
		std::cerr << "root path can not open : " << location.root <<  std::endl;
		return (1);
	}
	if (!location.index.empty() && location.path == "/" && IndexHtmlCheck(location))
		return (1);
	if (!location.upload_path.empty() && dirCheck(location.upload_path))
	{
		std::cerr << "Upload path can not open : " << location.upload_path << std::endl;
		return (1);
	}
	if (!location.cgi_path.empty() && access(location.cgi_path.c_str(), X_OK) != 0)
	{
		std::cerr << "Cgi path invalid: " << location.cgi_path << std::endl;
		return (1);
	}
	if (!location.allowed_methods.empty())
	{
		for (size_t i = 0; i < location.allowed_methods.size(); i++)
		{
			if (location.allowed_methods[i] != "GET"
				&&  location.allowed_methods[i] != "POST"
				 && location.allowed_methods[i] != "DELETE")
				{
					std::cerr << "Allowed method not valid : " << location.allowed_methods[i] << std::endl;
					return (1);
				}
		}
	}
	return (0);
}


