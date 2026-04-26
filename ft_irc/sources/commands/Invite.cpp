#include "Server.hpp"

static int	findFdByNick(const std::map<int, Client> &clients, const std::string &nick)
{
	for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == nick)
			return (it->first);
	}
	return (-1);
}

void	Server::cmdInvite(int fd, const std::string &params)
{
	Client	&client = _clients.find(fd)->second;

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + _name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	size_t	space = params.find(' ');
	if (space == std::string::npos)
	{
		sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " INVITE :Not enough parameters");
		return ;
	}

	const std::string	targetNick = params.substr(0, space);
	const std::string	channelName = params.substr(space + 1);

	if (!_channels.count(channelName))
	{
		sendReply(fd, ":" + _name + ERR_NOSUCHCHANNEL + client.getNickname() + " " + channelName + " :No such channel");
		return ;
	}

	Channel	&channel = _channels.find(channelName)->second;

	// El que invita debe estar en el canal
	if (!channel.hasMember(fd))
	{
		sendReply(fd, ":" + _name + ERR_NOTONCHANNEL + client.getNickname() + " " + channelName + " :You're not on that channel");
		return ;
	}

	if (channel.isInviteOnly() && !channel.isAdmin(fd))
	{
		sendReply(fd, ":" + _name + ERR_CHANOPRIVSNEEDED + client.getNickname() + " " + channelName + " :You're not channel operator");
		return ;
	}

	int	targetFd = findFdByNick(_clients, targetNick);
	if (targetFd == -1)
	{
		sendReply(fd, ":" + _name + ERR_NOSUCHNICK + client.getNickname() + " " + targetNick + " :No such nick");
		return ;
	}

	if (channel.hasMember(targetFd))
	{
		sendReply(fd, ":" + _name + ERR_USERONCHANNEL + client.getNickname() + " " + targetNick + " " + channelName + " :is already on channel");
		return ;
	}

	channel.addInvited(targetFd);
	const std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();

	sendReply(fd, ":" + _name + RPL_INVITING + client.getNickname() + " " + targetNick + " " + channelName);
	sendReply(targetFd, prefix + " INVITE " + targetNick + " " + channelName);
}
