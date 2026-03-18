/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitUtils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:06:03 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/13 15:06:04 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

int	numberCheck(std::string &value)
{
	if (!value.empty() && value[value.length() - 1] == ';')
		value.resize(value.size() - 1);
	for (size_t i = 0; i < value.size(); i++)
	{
		if (!std::isdigit(value[i]))
			return (0);
	}
	return (1);
}

std::string getValue(std::stringstream &ss)
{
	std::string value;
	ss >> value;
	if (!value.empty() && value[value.length() - 1] == ';')
		value.resize(value.size() - 1);
	return (value);
}

int dirCheck(std::string &file)
{
	DIR *dir = opendir(file.c_str());
	if (dir == NULL)
		return (1);
	closedir(dir);
	return (0);
}

int	strIsSpaceCheck(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isspace(str[i]))
			return (1);
	}
	return (0);
}

std::string ScopeAndHashCheck(std::string &word, int &scope, std::stringstream &ss)
{
	if (word[0] == '#')
		return ("continue");
	if (word == "{")
	{
		if (scope == true)
		{
			std::cerr << "Scope Error" << std::endl;
			return ("fail");
		}
		if (ss >> word && word[0] != '#')
		{
			std::cerr << "Invalid syntax after location block start: " << word << std::endl;
			return ("fail");
		}
		scope = true;
		return ("continue");
	}
	if (word == "}")
	{
		if (scope != true)
		{
			std::cerr << "Scope Error" << std::endl;
			return ("fail");
		}
		scope = false;
		return ("break");
	}
	return ("0");
}
