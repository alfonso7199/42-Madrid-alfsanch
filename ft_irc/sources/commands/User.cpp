/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:21:11 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/15 19:21:18 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdUser(int fd, const std::string &params)
{
	Client						&client = this->_clients.find(fd)->second;
	std::string					username;
	size_t						space = params.find(' ');
	size_t						colon = params.find(':');

	if (client.isRegistered())
	{
		sendReply(fd, ":" + this->_name + ERR_ALREADYREGISTERED + client.getNickname() + " :You may not register");
		return ;
	}
	if (space != std::string::npos)
		username = params.substr(0, space);
	else
		username = params;
	if (username.empty())
	{
		sendReply(fd, ":" + this->_name + ERR_NEEDMOREPARAMS + "* USER :Not enough parameters!");
		return ;
	}
	client.setUsername(username);
	if (colon != std::string::npos)
		client.setRealname(params.substr(colon + 1));
	tryRegister(fd);
}
