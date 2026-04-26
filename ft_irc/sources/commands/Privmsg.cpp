#include "Server.hpp"

void	Server::cmdPrivmsg(int fd, const std::string &params)
{
	Client		&client = this->_clients.find(fd)->second;
	size_t		space = params.find(' ');

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + this->_name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	if (params.empty() || space == std::string::npos)
	{
		if (params.empty())
			sendReply(fd, ":" + this->_name + ERR_NORECIPIENT + client.getNickname() + " :No recipient given (PRIVMSG)");
		else
			sendReply(fd, ":" + this->_name + ERR_NOTEXTTOSEND + client.getNickname() + " :No text to send");
		return ;
	}

	std::string	message = params.substr(space + 1);
	if (!message.empty() && message[0] == ':')
		message = message.substr(1);
	if (message.empty())
	{
		sendReply(fd, ":" + this->_name + ERR_NOTEXTTOSEND + client.getNickname() + " :No text to send");
		return ;
	}

	std::string	target = params.substr(0, space);
	if (target.empty())
	{
		sendReply(fd, ":" + this->_name + ERR_NORECIPIENT + client.getNickname() + " :No recipient given (PRIVMSG)");
		return ;
	}

	std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();

	if (target[0] == '#')
	{
		if (!this->_channels.count(target))
		{
			sendReply(fd, ":" + this->_name + ERR_NOSUCHCHANNEL + client.getNickname() + " " + target + " :No such channel");
			return ;
		}

		Channel	&channel = this->_channels.find(target)->second;
		if (!channel.hasMember(fd))
		{
			sendReply(fd, ":" + this->_name + ERR_CANNOTSENDTOCHAN + client.getNickname() + " " + target + " :Cannot send to channel");
			return;
		}
		channel.broadcast(prefix + " PRIVMSG " + target + " :" + message, fd);
//		std::vector<int>	failed = channel.broadcast(prefix + " PRIVMSG " + target + " :" + message, fd);
//		for (size_t i = 0; i < failed.size(); i++)
//			disconnectClient(failed[i]);
	}
	else
	{
		std::map<int, Client>::iterator	it = this->_clients.begin();
		while (it != this->_clients.end())
		{
			if (it->second.getNickname() == target)
			{
				sendReply(it->first, prefix + " PRIVMSG " + target + " :" + message);
				return ;
			}
			++it;
		}
		sendReply(fd, ":" + this->_name + ERR_NOSUCHNICK + client.getNickname() + " " + target + " :No such nick/channel");
	}
}
