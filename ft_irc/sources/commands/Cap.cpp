/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:19:02 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/17 21:45:26 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::cmdCap(int fd, const std::string &params)
{
	std::string	subcommand;
	size_t		space = params.find(' ');
	
	if (space != std::string::npos)
		subcommand = params.substr(0, space);
	else
		subcommand = params;

	if (subcommand == "LS")
		sendReply(fd, ":" + this->_name + " CAP * LS :");
	else if (subcommand == "REQ")
	{
		std::string	caps = (space != std::string::npos) ? params.substr(space + 1) : "";
		sendReply(fd, ":" + this->_name + " CAP * NAK :" + caps);
	}
	else if (subcommand == "END")
		tryRegister(fd);
}
