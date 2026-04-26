#include "Server.hpp"

void	Server::cmdKick(int fd, const std::string &params)
{
	Client		&client = _clients.find(fd)->second;

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + _name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	size_t	space1 = params.find(' ');
	if (space1 == std::string::npos)
	{
		sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " KICK :Not enough parameters");
		return ;
	}

	std::string	channelName = params.substr(0, space1);
	std::string	rest = params.substr(space1 + 1);
	std::string	targetNick;
	std::string	reason = "Kicked";

	size_t	space2 = rest.find(' ');
	if (space2 != std::string::npos)
	{
		targetNick = rest.substr(0, space2);
		reason = rest.substr(space2 + 1);
		if (!reason.empty() && reason[0] == ':')
			reason = reason.substr(1);
	}
	else
		targetNick = rest;

	// Verificar que el canal existe
	if (!_channels.count(channelName))
	{
		sendReply(fd, ":" + _name + ERR_NOSUCHCHANNEL + client.getNickname() + " " + channelName + " :No such channel");
		return ;
	}

	Channel	&channel = _channels.find(channelName)->second;

	if (!channel.hasMember(fd))
	{
		sendReply(fd, ":" + _name + ERR_NOTONCHANNEL + client.getNickname() + " " + channelName + " :You're not on that channel");
		return ;
	}

	if (!channel.isAdmin(fd))
	{
		sendReply(fd, ":" + _name + ERR_CHANOPRIVSNEEDED + client.getNickname() + " " + channelName + " :You're not channel operator");
		return ;
	}

	int	targetFd = -1;
	std::map<int, Client>::iterator	it = _clients.begin();
	while (it != _clients.end())
	{
		if (it->second.getNickname() == targetNick)
		{
			targetFd = it->first;
			break ;
		}
		++it;
	}

	if (targetFd == -1 || !channel.hasMember(targetFd))
	{
		sendReply(fd, ":" + _name + ERR_USERNOTINCHANNEL + client.getNickname() + " " + targetNick + " " + channelName + " :They aren't on that channel");
		return ;
	}

	std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();
	channel.broadcast(prefix + " KICK " + channelName + " " + targetNick + " :" + reason);
//	std::vector<int>	failed = channel.broadcast(prefix + " KICK " + channelName + " " + targetNick + " :" + reason);
//	for (size_t i = 0; i < failed.size(); i++)
//		disconnectClient(failed[i]);

	if (!_channels.count(channelName))
		return ;

	Channel	&chan = _channels.find(channelName)->second;
	chan.removeMember(targetFd);

	if (chan.getMemberCount() > 0)
	{
		std::map<int, Client *>	&members = chan.getMembers();
		std::string				namesList = "";

		for (std::map<int, Client *>::iterator it = members.begin(); it != members.end(); ++it)
		{
			if (!namesList.empty())
				namesList += " ";
			if (chan.isAdmin(it->first))
				namesList += "@";
			namesList += it->second->getNickname();
		}

		for (std::map<int, Client *>::iterator it = members.begin(); it != members.end(); ++it)
		{
			sendReply(it->first, ":" + _name + RPL_NAMREPLY + it->second->getNickname() + " = " + channelName + " :" + namesList);
			sendReply(it->first, ":" + _name + RPL_ENDOFNAMES + it->second->getNickname() + " " + channelName + " :End of /NAMES list");
		}
	}
}
