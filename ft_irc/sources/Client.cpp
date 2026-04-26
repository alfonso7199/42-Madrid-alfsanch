/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:22:39 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/24 19:41:07 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <sys/socket.h>

Client::Client(int fd, const std::string &hostname) :
_fd(fd), _nickname(""), _username(""), _realname(""),
_hostname(hostname), _buffer(""), _passOk(false), _registered(false)
{
	return ;
}

Client::Client(const Client &other) :
_fd(other._fd), _nickname(other._nickname), _username(other._username),
_realname(other._realname), _hostname(other._hostname),
_buffer(other._buffer), _outBuf(other._outBuf), _passOk(other._passOk),
_registered(other._registered)
{
	return ;
}

Client	&Client::operator=(const Client &other)
{
	if (this != &other)
	{
		this->_fd = other._fd;
		this->_nickname = other._nickname;
		this->_username = other._username;
		this->_realname = other._realname;
		this->_hostname = other._hostname;
		this->_buffer = other._buffer;
		this->_passOk = other._passOk;
		this->_registered = other._registered;
		this->_outBuf = other._outBuf;
	}
	return (*this);
}

Client::~Client(void)
{
	return ;
}

int	Client::getFd(void) const
{
	return (this->_fd);
}

const std::string	&Client::getNickname(void) const
{
	return (this->_nickname);
}

const std::string	&Client::getUsername(void) const
{
	return (this->_username);
}

const std::string	&Client::getRealname(void) const
{
	return (this->_realname);
}

const std::string	&Client::getHostname(void) const
{
	return (this->_hostname);
}

std::string	&Client::getBuffer(void)
{
	return (this->_buffer);
}

bool	Client::isPassOk(void) const
{
	return (this->_passOk);
}

bool	Client::isRegistered(void) const
{
	return (this->_registered);
}

void	Client::setNickname(const std::string &nickname)
{
	this->_nickname = nickname;
}

void	Client::setUsername(const std::string &username)
{
	this->_username = username;
}

void	Client::setRealname(const std::string &realname)
{
	this->_realname = realname;
}

void	Client::setPassOk(bool ok)
{
	this->_passOk = ok;
}

void	Client::setRegistered(bool registered)
{
	this->_registered = registered;
}

/*
ssize_t	Client::send(const std::string &msg) const
{
	std::string	full = msg + "\r\n";
	
	return (::send(this->_fd, full.c_str(), full.size(), 0));
} */

std::string	&Client::getOutBuf(void)
{
	return (this->_outBuf);
}

bool	Client::hasPendingOut(void) const
{
	return (!this->_outBuf.empty());
}

void	Client::queueOut(const std::string &msg)
{
	this->_outBuf += msg + "\r\n";
}

std::ostream	&operator<<(std::ostream &os, const Client &c)
{
	os << c.getNickname() << "!" << c.getUsername() << "@" << c.getHostname();
	return (os);
}
