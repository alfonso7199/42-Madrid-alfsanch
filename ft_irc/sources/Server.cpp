/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 17:42:49 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/24 20:41:49 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) : _name("Unknown"), _port(6667), _passwd("")
{
	return ;
}

Server::Server(const std::string &name, int port, const std::string &passwd)
: _name(name), _port(port), _passwd(passwd)
{
	return ;
}

Server::Server(const Server &other) :
_name(other._name), _port(other._port), _passwd(other._passwd),
_pollfds(other._pollfds), _clients(other._clients), _channels(other._channels)
{
	return ;
}

Server	&Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_port = other._port;
		this->_passwd = other._passwd;
		this->_channels = other._channels;
		this->_clients = other._clients;
		this->_pollfds = other._pollfds;
	}
	return (*this);
}

Server::~Server(void)
{
	return ;
}

// ===========================================================================
// Setters
// ===========================================================================
void	Server::setPort(int port)
{
	this->_port = port;
}

void	Server::setName(std::string name)
{
	this->_name = name;
}

void	Server::setPasswd(std::string passwd)
{
	this->_passwd = passwd;
}

// ===========================================================================
// Getters
// ===========================================================================
const std::string	&Server::getName(void) const
{
	return (this->_name);
}

int	Server::getPort(void) const
{
	return (this->_port);
}

const std::string	&Server::getPasswd(void) const
{
	return (this->_passwd);
}

void	Server::sendReply(int fd, const std::string &msg)
{
	std::map<int, Client>::iterator	it = _clients.find(fd);
	if (it == _clients.end())
		return ;
	it->second.queueOut(msg);
}

void	Server::tryRegister(int fd)
{
	Client					&client = this->_clients.find(fd)->second;

	if (client.isRegistered())
		return ;
	if ((!client.isPassOk() && !this->_passwd.empty()) || client.getNickname().empty() || client.getUsername().empty())
		return ;
	client.setRegistered(true);
	sendReply(fd, ":" + this->_name + RPL_WELCOME  + client.getNickname() + " :Welcome to ft_irc! " + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname());
	sendReply(fd, ":" + this->_name + RPL_YOURHOST + client.getNickname() + " :Your host is " + this->_name + ", running ft_irc");
	sendReply(fd, ":" + this->_name + RPL_CREATED  + client.getNickname() + " :This server was created recently");
	sendReply(fd, ":" + this->_name + RPL_MYINFO   + client.getNickname() + " " + this->_name + " ft_irc o itkol");
	sendReply(fd, ":" + this->_name + ERR_NOMOTD   + client.getNickname() + " :MOTD File is missing");
}

// WeeChat: CAP LS 302, PASS <senha>, NICK <nick>, USER <user> ..., CAP END
void	Server::start(int port)
{
	int				fd = 0;
	struct	pollfd	pfd;
	std::string		hostname;

	fd = initServerSocket(port);
	if (fd < 0)
		return ;
	pfd.fd = fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	this->_pollfds.push_back(pfd);
	while (!g_stop)
	{
		for (size_t k = 0; k < _pollfds.size(); k++)
		{
			int								fdk = _pollfds[k].fd;
			short							ev = POLLIN;
			std::map<int, Client>::iterator	cit = _clients.find(fdk);
			if (cit != _clients.end() && cit->second.hasPendingOut())
				ev |= POLLOUT;
			_pollfds[k].events = ev;
		}

		int	ready = poll(this->_pollfds.data(), this->_pollfds.size(), 1000); // Timeout 1000 msd, instead of -1

		if (g_stop)
			break ;
		if (ready < 0)
		{
//			if (errno == EINTR) // pool can return (-1), so with errno == EINTR interrupt, it's not an error
//				continue ;
//			perror("Poll");
//			break ;
			continue ;
		}

		size_t	i = 0;
		while (i < this->_pollfds.size())
		{
			if (this->_pollfds[i].revents == 0)
			{
				i++;
				continue ;
			}

			if (_pollfds[i].fd == fd && (_pollfds[i].revents & POLLIN))
			{
				int	clientFd = acceptConnection(fd, hostname);
				if (clientFd != -1)
				{
					this->_clients.insert(std::make_pair(clientFd, Client(clientFd, hostname)));
					struct pollfd cpfd;
					cpfd.fd = clientFd;
					cpfd.events = POLLIN;
					cpfd.revents = 0;
					this->_pollfds.push_back(cpfd);
				}
				i++;
				continue ;
			}

			bool	disconnected = false;

			// 1) POLLIN: recv + parse
			if (_pollfds[i].revents & POLLIN)
			{
				char	buf[BUFFER_LIMIT_SIZE];
				int		bytes = recv(_pollfds[i].fd, buf, sizeof(buf) - 1, 0);
				if (bytes <= 0)
				{
					disconnectClient(_pollfds[i].fd);
					disconnected = true;
				}
				else
				{
					buf[bytes] = '\0';
					std::string	&cbuf = _clients.find(_pollfds[i].fd)->second.getBuffer();
					cbuf += buf;
					if (cbuf.size() > BUFFER_LIMIT_SIZE)
					{
						disconnectClient(_pollfds[i].fd);
						disconnected = true;
					}
					else
					{
						size_t	pos;

						while ((pos = cbuf.find("\r\n")) != std::string::npos)
						{
							std::string	cmd = cbuf.substr(0, pos);
							cbuf.erase(0, pos + 2);
							if (!cmd.empty())
							{
								int	curFd = _pollfds[i].fd;
								handleCommand(curFd, cmd);
								if (this->_clients.find(curFd) == this->_clients.end())
								{
									disconnected = true;
									break ;
								}
							}
						}
					}
				}
			}

			// POLLOUT
			if (!disconnected && (_pollfds[i].revents & POLLOUT))
			{
				std::map<int, Client>::iterator	cit = _clients.find(_pollfds[i].fd);
				if (cit != _clients.end())
				{
					std::string	&out = cit->second.getOutBuf();
					if (!out.empty())
					{
						ssize_t	n = ::send(_pollfds[i].fd, out.data(), out.size(), MSG_NOSIGNAL);
						if (n > 0)
							out.erase(0, n); // No change in errno. POLLHUP/POLLERR on error
					}
				}
			}

			// POLLHUP / POLLERR: disconnection
			if (!disconnected && (_pollfds[i].revents & (POLLHUP | POLLERR)))
			{
				disconnectClient(_pollfds[i].fd);
				disconnected = true;
			}

			if (disconnected)
				i--;
			i++;
		}
	}
	std::cout << "\nShutting down..." << std::endl;
	for (size_t i = 0; i < this->_pollfds.size(); i++)
		close(this->_pollfds[i].fd);
	this->_pollfds.clear();
	this->_clients.clear();
	this->_channels.clear();
}

void	Server::handleCommand(int fd, const std::string &cmd)
{
	std::string	command;
	std::string	params;
	size_t		space;

	space = cmd.find(' ');
	if (space != std::string::npos)
	{
		command = cmd.substr(0, space);
		params = cmd.substr(space + 1);
	}
	else
		command = cmd;

	for (size_t j =0; j < command.size(); j++)
		command[j] = std::toupper(command[j]);
	std::cout << "[fd = " << fd << "] CMD: " << command << " | PARAMS: " << params << std::endl;
	if (command != "CAP" && command != "PASS" &&
		command != "NICK" && command != "USER" &&
		command != "QUIT" && command != "PING")
	{
		if (this->_clients.find(fd)->second.isRegistered() == false)
		{
			sendReply(fd, ":" + this->_name + ERR_NOTREGISTERED + "* :You have not registered");
			return ;
		}
	}
	if (command == "CAP")
		cmdCap(fd, params);
	else if (command == "PASS")
		cmdPass(fd, params);
	else if (command == "NICK")
		cmdNick(fd, params);
	else if (command == "USER")
		cmdUser(fd, params);
	else if (command == "JOIN")
		cmdJoin(fd, params);
	else if (command == "PART")
		cmdPart(fd, params);
	else if (command == "PRIVMSG")
		cmdPrivmsg(fd, params);
	else if (command == "INVITE")
		cmdInvite(fd, params);
	else if (command == "TOPIC")
		cmdTopic(fd, params);
	else if (command == "MODE")
		cmdMode(fd, params);
	else if (command == "KICK")
		cmdKick(fd, params);
	else if (command == "QUIT")
		cmdQuit(fd, params);
	else if (command == "PING")
		sendReply(fd, ":" + this->_name + " PONG " + this->_name + " " + params); // Adjusting PONG message to avoid disconnection in modern IRC clients
//		sendReply(fd, "PONG " + params);

/*
	else if (command == "OPER")
		cmdOper(fd, params);
	else if (command == "PART")
		cmdPart(fd, params);
	else if (command == "NAMES")
		cmdNames(fd, params);
	else if (command == "LIST")
		cmdList(fd, params);
	else if (command == "KILL")
		cmdKill(fd, params);
*/
}

int	Server::initServerSocket(int port)
{
	int					fd;
	int					opt = 1;
	struct sockaddr_in	addr = {};

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
	{
		std::cerr << "Error: Socket() failed" << std::endl;
		return (-1);
	}

	// Avoid error 'Address already in use' on restart
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// Set socket as non-block
	fcntl(fd, F_SETFL, O_NONBLOCK);

	addr.sin_family = AF_INET; // Use IPv4
	addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
	addr.sin_port = htons(port);	// Convert byte order

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		std::cerr << "Error: Bind() failed " << std::endl;
		close(fd);
		return (-1);
	}

	if (listen(fd, SOMAXCONN) < 0)
	{
		std::cerr << "Error: Listen() failed " << std::endl;
		close(fd);
		return (-1);
	}
	return (fd);
}

int	Server::acceptConnection(int serverFd, std::string &hostname)
{
	struct sockaddr_in	clientAddr;
	socklen_t			addrLen;
	int					clientFd;
	char				ip[INET_ADDRSTRLEN];

	addrLen = sizeof(clientAddr);
	clientFd = accept(serverFd, (struct sockaddr*)&clientAddr, &addrLen);
	if (clientFd < 0)
	{
//		if (errno != EAGAIN && errno != EWOULDBLOCK) // Check if there is no pending connections
//			perror("Accept");
		return (-1);
	}

	fcntl(clientFd, F_SETFL, O_NONBLOCK);
	inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));
	std::cout << "New connection from: " << ip << std::endl;
	hostname = ip;
	return (clientFd);
}

std::ostream	&operator<<(std::ostream &os, const Server &s)
{
	os << '\n' << "IRC Server Details " << '\n';
	os << "- " << s.getName() << '\n';
	os << "- " << s.getPort() << '\n';
	os << "- " << s.getPasswd() << '\n';
	return (os);
}
