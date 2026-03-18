/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParsingHttp.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:01:55 by atursun           #+#    #+#             */
/*   Updated: 2026/03/13 15:24:25 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../includes/Config.hpp"

std::string     directory_listing(std::string file_path, std::string request_path);
void			handle_file(std::string body, std::string file_path, int fd);
bool 			isMethodAllowed(LocationConfig* location, const std::string& method);
