/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:16:50 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/15 19:17:28 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdPass(int fd, const std::string &params)
{
	Client		&client = this->_clients.find(fd)->second;
	std::string	password = params;

	if (client.isRegistered())
	{
		sendReply(fd, ":" + this->_name + ERR_ALREADYREGISTERED + client.getNickname() + " :You may not register");
		return ;
	}
	if (!password.empty() && password[0] == ':')
		password = password.substr(1);
	if (password.empty())
	{
		sendReply(fd, ":" + this->_name + ERR_NEEDMOREPARAMS + "* PASS :Not enough parameters");
		return ;
	}
	if (password == this->_passwd)
		client.setPassOk(true);
	else
		sendReply(fd, ":" + this->_name + ERR_PASSWDMISMATCH + "* PASS :Incorrect");
}
