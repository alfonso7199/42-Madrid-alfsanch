#include "Server.hpp"

static bool	parseTopicParams(const std::string &params, std::string &channelName,
								std::string &newTopic, bool &settingTopic)
{
	if (params.empty())
		return (false);

	size_t	space = params.find(' ');
	channelName = (space != std::string::npos) ? params.substr(0, space) : params;
	settingTopic = (space != std::string::npos);

	if (settingTopic)
	{
		newTopic = params.substr(space + 1);
		if (!newTopic.empty() && newTopic[0] == ':')
			newTopic = newTopic.substr(1);
	}
	return (true);
}

void	Server::cmdTopic(int fd, const std::string &params)
{
	Client		&client = _clients.find(fd)->second;
	std::string	channelName;
	std::string	newTopic;
	bool		settingTopic = false;

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + _name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	if (!parseTopicParams(params, channelName, newTopic, settingTopic))
	{
		sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " TOPIC :Not enough parameters");
		return ;
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

	if (!settingTopic)
	{
		if (channel.getTopic().empty())
			sendReply(fd, ":" + _name + RPL_NOTOPIC + client.getNickname() + " " + channelName + " :No topic is set");
		else
			sendReply(fd, ":" + _name + RPL_TOPIC + client.getNickname() + " " + channelName + " :" + channel.getTopic());
		return ;
	}

	if (channel.isTopicRestricted() && !channel.isAdmin(fd))
	{
		sendReply(fd, ":" + _name + ERR_CHANOPRIVSNEEDED + client.getNickname() + " " + channelName + " :You're not channel operator");
		return ;
	}

	channel.setTopic(newTopic);
	const std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();
	channel.broadcast(prefix + " TOPIC " + channelName + " :" + newTopic);
//	std::vector<int>	failed = channel.broadcast(prefix + " TOPIC " + channelName + " :" + newTopic);
//	for (size_t i = 0; i < failed.size(); i++)
//		disconnectClient(failed[i]);
}
