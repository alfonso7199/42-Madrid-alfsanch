#include "Server.hpp"

static std::string	buildNamesList(Channel &channel)
{
	std::string						names;
	std::map<int, Client *>			&members = channel.getMembers();
	std::map<int, Client *>::iterator	it = members.begin();

	while (it != members.end())
	{
		if (channel.isAdmin(it->first))
			names += "@";
		names += it->second->getNickname();
		++it;
		if (it != members.end())
			names += " ";
	}
	return (names);
}

void	Server::cmdJoin(int fd, const std::string &params)
{
	Client		&client = _clients.find(fd)->second;
	std::string	channelName;
	std::string	key;
	size_t		space = params.find(' ');

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + _name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	if (space != std::string::npos)
	{
		channelName = params.substr(0, space);
		key = params.substr(space + 1);
		if (!key.empty() && key[0] == ':')
			key = key.substr(1);
	}
	else
		channelName = params;

	if (channelName == "0")
	{
		std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();
		std::vector<std::string>	toLeave;
		for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		{
			if (it->second.hasMember(fd))
				toLeave.push_back(it->first);
		}
		for (size_t n = 0; n < toLeave.size(); n++)
		{
			if (!_channels.count(toLeave[n]))
				continue ;
			Channel	&ch = _channels.find(toLeave[n])->second;
			ch.broadcast(prefix + " PART " + toLeave[n] + " :Left all channels");
			ch.removeMember(fd);
			if (ch.getMemberCount() == 0)
				_channels.erase(toLeave[n]);
		}
		return ;
	}

	if (channelName.empty() || channelName[0] != '#')
	{
		sendReply(fd, ":" + _name + ERR_NOSUCHCHANNEL + client.getNickname() + " " + channelName + " :No such channel");
		return ;
	}

	if (_channels.count(channelName))
	{
		Channel	&channel = _channels.find(channelName)->second;

		if (channel.hasMember(fd))
			return ;

		if (channel.isInviteOnly() && !channel.isInvited(fd))
		{
			sendReply(fd, ":" + _name + ERR_INVITEONLYCHAN + client.getNickname() + " " + channelName + " :Cannot join channel (+i)");
			return ;
		}

		if (!channel.getPasswordChannel().empty() && channel.getPasswordChannel() != key)
		{
			sendReply(fd, ":" + _name + ERR_BADCHANNELKEY + client.getNickname() + " " + channelName + " :Cannot join channel (+k)");
			return ;
		}

		if (channel.getUserLimit() > 0 && channel.getMemberCount() >= channel.getUserLimit())
		{
			sendReply(fd, ":" + _name + ERR_CHANNELISFULL + client.getNickname() + " " + channelName + " :Cannot join channel (+l)");
			return ;
		}

		channel.addMember(&client);
	}
	else
	{
		_channels.insert(std::make_pair(channelName, Channel(channelName)));
		Channel	&channel = _channels.find(channelName)->second;
		channel.addMember(&client);
		channel.addAdmin(fd);
	}

	Channel		&channel = _channels.find(channelName)->second;

	if (channel.isInviteOnly())
		channel.removeInvited(fd);
	
	std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();
	channel.broadcast(prefix + " JOIN " + channelName);
//	std::vector<int>	failed = channel.broadcast(prefix + " JOIN " + channelName);
//	for (size_t i = 0; i < failed.size(); i++)
//		disconnectClient(failed[i]);

	if (!_clients.count(fd) || !_channels.count(channelName))
		return ;

	Channel	&ch = _channels.find(channelName)->second;
	if (ch.getTopic().empty())
		sendReply(fd, ":" + _name + RPL_NOTOPIC + client.getNickname() + " " + channelName + " :No topic is set");
	else
		sendReply(fd, ":" + _name + RPL_TOPIC + client.getNickname() + " " + channelName + " :" + ch.getTopic());

	sendReply(fd, ":" + _name + RPL_NAMREPLY + client.getNickname() + " = " + channelName + " :" + buildNamesList(ch));
	sendReply(fd, ":" + _name + RPL_ENDOFNAMES + client.getNickname() + " " + channelName + " :End of /NAMES list");
}