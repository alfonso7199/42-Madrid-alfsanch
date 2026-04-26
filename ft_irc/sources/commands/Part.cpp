#include "Server.hpp"

void	Server::cmdPart(int fd, const std::string &params)
{
	Client	&client = _clients.find(fd)->second;

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + _name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	if (params.empty())
	{
		sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " PART :Not enough parameters");
		return ;
	}

	size_t		space = params.find(' ');
	std::string	channelName = (space != std::string::npos) ? params.substr(0, space) : params;
	std::string	reason = "";
	if (space != std::string::npos)
	{
		reason = params.substr(space + 1);
		if (!reason.empty() && reason[0] == ':')
			reason = reason.substr(1);
	}

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

	const std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();
	const std::string	partMsg = prefix + " PART " + channelName + (reason.empty() ? "" : " :" + reason);

	// Broadcast PART a todos los miembros, incluido el que sale
	channel.broadcast(partMsg);
//	std::vector<int>	failed = channel.broadcast(partMsg);
//	for (size_t i = 0; i < failed.size(); i++)
//		disconnectClient(failed[i]);

	if (_clients.count(fd) && _channels.count(channelName))
	{
		channel.removeMember(fd);
		if (channel.getMemberCount() == 0)
			_channels.erase(channelName);
	}
}
