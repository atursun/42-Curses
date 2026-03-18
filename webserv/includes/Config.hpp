/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:20 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/15 16:45:06 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#define CLIENT_TIMEOUT 30

#include "ServerConfig.hpp"
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <cstring>
#include <sstream>
#include <dirent.h>
#include <csignal>
#include <cerrno>
#include "ParsingHttp.hpp"


extern volatile sig_atomic_t g_signal;

class Config {
private:
	std::vector<ServerConfig>   Servers;
	std::ifstream               configFile;
	std::map<int, ServerConfig*> client_to_server;
	std::vector<std::string>    messages; 
    std::map<int, time_t>       client_activity_time;
	
public:
	std::vector<struct pollfd>  poll_fds;
	Config();
	~Config();
    void    inactive_client_check();
	int		initConfig();
	void    startServer();
	int     new_user_check(int i);
	int     setupConfig(int i);
	int    	fileCheck(char *arg);
	int		SetLocation(std::string &line, ServerConfig &server);
	int		listenCheck(std::stringstream &ss, ServerConfig &server);
	int		configWordCheck(std::stringstream &ss, std::string word, ServerConfig &server, std::string &line);
	int		configLocationWordCheck(std::stringstream &ss, std::string word, LocationConfig &location);
	const std::vector<ServerConfig>& getServers() const;
};
std::pair<int, std::string>	errorPage(std::stringstream &ss, ServerConfig &server);
std::string					getValue(std::stringstream &ss);
int							numberCheck(std::string &value);
int							hostCheck(std::string &str);
std::string					ScopeAndHashCheck(std::string &word, int &scope, std::stringstream &ss);
int							dirCheck(std::string &file);
int							strIsSpaceCheck(std::string &str);

#endif