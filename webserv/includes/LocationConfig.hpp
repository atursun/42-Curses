/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:24 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/15 16:45:14 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP

# include <string>
# include <vector>
# include <map>
# include <iostream>
# include <cstdlib>

class LocationConfig {
public:
    std::string             path;           
    std::string             root;           
    std::string             index;          
    std::string             cgi_path;       
    std::string             cgi_ext;        
    std::string             upload_path;    
    std::string             redirect_url;   
    bool                    autoindex;      
    std::vector<std::string> allowed_methods; 
    bool                    IsReturn;
    std::string             return_code;
    std::string             return_url;
    unsigned long           client_max_body_size; 
    LocationConfig();
};

int LocationCheck(LocationConfig &location);


#endif