/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:41:15 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/24 19:36:51 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <exception>
# include <netinet/in.h>
# include <unistd.h>
# include <cstdio>
# include <cstring>
# include <cstdlib>
# include <csignal>
# include <fcntl.h>			//	
# include <fstream>			//	
# include <sys/socket.h>	//	
# include <arpa/inet.h>		//	accept
# include <vector>
# include <map>
# include <poll.h>

# include "Client.hpp"
# include "Channel.hpp"

# define RPL_WELCOME          " 001 "
# define RPL_YOURHOST         " 002 "
# define RPL_CREATED          " 003 "
# define RPL_MYINFO           " 004 "
# define RPL_CHANNELMODEIS    " 324 "
# define RPL_INVITING         " 341 "
# define RPL_NOTOPIC          " 331 "
# define RPL_TOPIC            " 332 "
# define RPL_NAMREPLY         " 353 "
# define RPL_ENDOFNAMES       " 366 "

# define RPL_MOTDSTART        " 375 "
# define RPL_MOTD             " 372 "
# define RPL_ENDOFMOTD        " 376 "

# define ERR_NOSUCHNICK       " 401 "
# define ERR_CANNOTSENDTOCHAN " 404 "
# define ERR_NORECIPIENT      " 411 "
# define ERR_NOTEXTTOSEND     " 412 "

# define ERR_NOMOTD           " 422 "

# define ERR_NOSUCHCHANNEL    " 403 "
# define ERR_NONICKNAMEGIVEN  " 431 "
# define ERR_ERRONEUSNICKNAME " 432 "
# define ERR_NICKNAMEINUSE    " 433 "
# define ERR_USERNOTINCHANNEL " 441 "
# define ERR_NOTONCHANNEL     " 442 "
# define ERR_USERONCHANNEL    " 443 "
# define ERR_NOTREGISTERED    " 451 "
# define ERR_NEEDMOREPARAMS   " 461 "
# define ERR_ALREADYREGISTERED " 462 "
# define ERR_PASSWDMISMATCH   " 464 "
# define ERR_CHANNELISFULL    " 471 "
# define ERR_UNKNOWNMODE      " 472 "
# define ERR_INVITEONLYCHAN   " 473 "
# define ERR_BADCHANNELKEY    " 475 "
# define ERR_CHANOPRIVSNEEDED " 482 "

# define BUFFER_LIMIT_SIZE     4096
# define LOWER_PORT_ALLOWED    1024
# define HIGHER_PORT_ALLOWED   65535

extern volatile sig_atomic_t g_stop;

class Server
{
	private:
		std::string						_name;
		int								_port;
		std::string						_passwd;
		std::vector<struct pollfd>		_pollfds;
		std::map<int, Client>			_clients;
		std::map<std::string, Channel>	_channels;
	protected:
	public:
		Server(void);
		Server(const std::string &name, int port, const std::string &passwd);
		Server(const Server &other);
		Server	&operator=(const Server &other);
		~Server(void);

		void	setPort(int port);
		void	setName(std::string name);
		void	setPasswd(std::string passwd);

		const std::string	&getName(void) const;
		int					getPort(void) const;
		const std::string	&getPasswd(void) const;

		void	start(int port);
		int		initServerSocket(int port);
		int		acceptConnection(int serverFd, std::string &hostname);

		void	handleCommand(int fd, const std::string &cmd);
		void	sendReply(int fd, const std::string &msg);
		void	disconnectClient(int fd, const std::string &reason = "connection closed");

		void	cmdPass(int fd, const std::string &params);
		void	cmdNick(int fd, const std::string &params);
		void	cmdUser(int fd, const std::string &params);
		void	cmdCap(int fd, const std::string &params);
		/*
		Comandos, en principio estos, los comento para ver si nos sirven, por ahora creo que con esto es sufi
		Join para unirte a un canal
		Privmsg para msgs privados y puede que para enviar mensaje de un canal a todos sus usuarios?
		Kick para echar a alguien de un canal
		Invite para invitar a un canal
		Topic para cambiar el topic de un canal, +t elige quien puede cambiarlo
		Mode para cambair entre los modos del canal que nos dio el subject i t k o y l
		Quit para desconectarse limpiamente
		Disconect para limpiar al cliente de todos los canales
		*/
		void	cmdJoin(int fd, const std::string &params);
		void	cmdPart(int fd, const std::string &params);
		void	cmdPrivmsg(int fd, const std::string &params);
		void	cmdKick(int fd, const std::string &params);
		void	cmdInvite(int fd, const std::string &params);
		void	cmdTopic(int fd, const std::string &params);
		void	cmdMode(int fd, const std::string &params);
		void	cmdQuit(int fd, const std::string &params);

		void	tryRegister(int fd);
};

std::ostream	&operator<<(std::ostream &os, const Server &s);

#endif

