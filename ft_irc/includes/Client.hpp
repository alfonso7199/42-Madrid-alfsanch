/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 18:19:05 by rzamolo-          #+#    #+#             */
/*   Updated: 2026/04/23 17:05:37 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <iomanip>
# include <exception>
# include <string>
# include <sys/types.h>

class Client
{
	private:
		int         _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		std::string _hostname;
		std::string _buffer;
		std::string	_outBuf;
		bool        _passOk;
		bool        _registered;
	protected:
	public:
		Client(int fd, const std::string &hostname);
		Client(const Client &other);
		Client	&operator=(const Client &other);
		~Client(void);

		int					getFd(void) const;
		const std::string	&getNickname(void) const;
		const std::string	&getUsername(void) const;
		const std::string	&getRealname(void) const;
		const std::string	&getHostname(void) const;
		std::string			&getBuffer(void);
		std::string			&getOutBuf(void);
		bool				isPassOk(void) const;
		bool				isRegistered(void) const;
		bool				hasPendingOut(void) const;

		void	setNickname(const std::string &nickname);
		void	setUsername(const std::string &username);
		void	setRealname(const std::string &realname);
		void	setPassOk(bool ok);
		void	setRegistered(bool registered);

//		ssize_t	send(const std::string &msg) const;
		void	queueOut(const std::string &msg);
		
};

std::ostream	&operator<<(std::ostream &os, const Client &c);

#endif

