/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:33:52 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/20 22:42:30 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

volatile sig_atomic_t	g_stop = 0;

static void	handleSignal(int sig)
{
	(void)sig;
	g_stop = 1;
}

int	main(int argc, const char *argv[])
{
	struct sigaction	sa;

	sa.sa_handler = handleSignal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGPIPE, SIG_IGN);
	
	if (argc != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	char	*endptr;
	long	port = std::strtol(argv[1], &endptr, 10);

	if (*argv[1] == '\0' || *endptr != '\0' || port < LOWER_PORT_ALLOWED || port > HIGHER_PORT_ALLOWED)
	{
		std::cout << "Invalid port range!" << std::endl;
		return (2);	
	}
	Server	srv("ft_irc", port, argv[2]);
	srv.start(srv.getPort());
	return (0);
}
