/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:18:20 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/24 19:55:26 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <set>

static bool	isValidNickChar(unsigned char c, bool isFirst)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (true);
	// especiais RFC 2812: [ ] \ ` _ ^ { | }
	if (c == '[' || c == ']' || c == '\\' || c == '`' ||
		c == '_' || c == '^' || c == '{' || c == '|' || c == '}')
		return (true);
	if (isFirst)
		return (false);
	if (c >= '0' && c <= '9')
		return (true);
	if (c == '-')
		return (true);
	return (false);
}

static bool	isValidNick(const std::string &nick)
{
	if (nick.empty() || nick.size() > 30)
		return (false);
	for (size_t i = 0; i < nick.size(); i++)
	{
		if (!isValidNickChar(static_cast<unsigned char>(nick[i]), i == 0))
			return (false);
	}
	return (true);
}

void	Server::cmdNick(int fd, const std::string &params)
{
	Client	&client = _clients.find(fd)->second;

	if (params.empty())
	{
		sendReply(fd, ":" + _name + ERR_NONICKNAMEGIVEN + "* :No nickname given");
		return ;
	}

	std::string	newNick = params;
	if (!newNick.empty() && newNick[0] == ':')
		newNick = newNick.substr(1);

	if (!isValidNick(newNick))
	{
		sendReply(fd, ":" + _name + ERR_ERRONEUSNICKNAME + "* " + newNick + " :Erroneous nickname");
		return ;
	}

	// Comprobar que el nick no está ya en uso
	for (std::map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->first != fd && it->second.getNickname() == newNick)
		{
			sendReply(fd, ":" + _name + ERR_NICKNAMEINUSE + "* " + newNick + " :Nickname is already in use");
			return ;
		}
	}

	const std::string	oldNick = client.getNickname();

	if (oldNick == newNick)
		return ;

	client.setNickname(newNick);

	if (!client.isRegistered())
	{
		tryRegister(fd);
		return ;
	}
	const std::string	prefix = ":" + oldNick + "!" + client.getUsername() + "@" + client.getHostname();
	const std::string	nickMsg = prefix + " NICK " + newNick;

	std::set<int>	notified;
	sendReply(fd, nickMsg);
	notified.insert(fd);

	for (std::map<std::string, Channel>::iterator chIt = _channels.begin(); chIt != _channels.end(); ++chIt)
	{
		if (!chIt->second.hasMember(fd))
			continue ;

		std::map<int, Client *>	&members = chIt->second.getMembers();
		for (std::map<int, Client *>::iterator mIt = members.begin(); mIt != members.end(); ++mIt)
		{
			if (notified.count(mIt->first) == 0)
			{
				sendReply(mIt->first, nickMsg);
				notified.insert(mIt->first);
			}
		}
	}
}
