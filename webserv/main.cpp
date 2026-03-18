/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikkayma <mikkayma@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:35:40 by mikkayma          #+#    #+#             */
/*   Updated: 2026/03/13 15:14:03 by mikkayma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/Config.hpp"

volatile sig_atomic_t g_signal = 1;

void signal_handle(int signal)
{
    (void)signal;
    g_signal = 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid argument" << std::endl;
		return (1);
	}
	Config config;
	if (config.fileCheck(argv[1]))
		return (1);
	if (config.initConfig())
        return (1);

	for (size_t i = 0; i < config.getServers().size(); i++)
	{
		if (config.setupConfig(i))
            return (1);
	}
    std::signal(SIGINT, signal_handle);
	config.startServer();
    std::cout << "\nServer Closing" << std::endl;
}
