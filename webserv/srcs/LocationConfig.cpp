/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:35 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/06 13:10:00 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/LocationConfig.hpp"

LocationConfig::LocationConfig()
{
	this->path = "";
	this->root = "";
	this->index = "";
	this->cgi_path = "";
	this->cgi_ext = "";
	this->upload_path = "";
	this->redirect_url = "";
	this->autoindex = false;
	this->return_code = "";
	this->return_url = "";	
	this->IsReturn = false;
	this->client_max_body_size = 0;
}
