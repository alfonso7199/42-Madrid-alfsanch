#include "Server.hpp"
#include <sstream>
#include <cstdlib>

static int	findFdByNick(const std::map<int, Client> &clients, const std::string &nick)
{
	for (std::map<int, Client>::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == nick)
			return (it->first);
	}
	return (-1);
}

static void	parseModeParams(const std::string &params, std::string &target,
								std::string &modeStr, std::string &modeArgs)
{
	size_t	s1 = params.find(' ');
	target = (s1 != std::string::npos) ? params.substr(0, s1) : params;
	if (s1 == std::string::npos)
		return ;

	std::string	rest = params.substr(s1 + 1);
	size_t		s2 = rest.find(' ');
	if (s2 != std::string::npos)
	{
		modeStr = rest.substr(0, s2);
		modeArgs = rest.substr(s2 + 1);
	}
	else
		modeStr = rest;
}

static std::vector<std::string>	parseArgs(const std::string &modeArgs)
{
	std::vector<std::string>	args;
	std::istringstream			iss(modeArgs);
	std::string					token;

	while (iss >> token)
		args.push_back(token);
	return (args);
}

static std::string	buildCurrentModes(const Channel &channel, std::string &outParams)
{
	std::string	modes = "+";
	outParams = "";

	if (channel.isInviteOnly())
		modes += "i";
	if (channel.isTopicRestricted())
		modes += "t";
	if (!channel.getPasswordChannel().empty())
	{
		modes += "k";
		outParams += " " + channel.getPasswordChannel();
	}
	if (channel.getUserLimit() > 0)
	{
		modes += "l";
		std::ostringstream	ss;
		ss << channel.getUserLimit();
		outParams += " " + ss.str();
	}
	return (modes);
}

void	Server::cmdMode(int fd, const std::string &params)
{
	Client	&client = _clients.find(fd)->second;

	if (!client.isRegistered())
	{
		sendReply(fd, ":" + _name + ERR_NOTREGISTERED + "* :You have not registered");
		return ;
	}

	if (params.empty())
	{
		sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " MODE :Not enough parameters");
		return ;
	}

	std::string	target;
	std::string	modeStr;
	std::string	modeArgs;
	parseModeParams(params, target, modeStr, modeArgs);

	if (target.empty() || target[0] != '#')
	{
		if (!target.empty())
			sendReply(fd, ":" + _name + " 221 " + client.getNickname() + " :+");
		return ;
	}

	if (!_channels.count(target))
	{
		sendReply(fd, ":" + _name + ERR_NOSUCHCHANNEL + client.getNickname() + " " + target + " :No such channel");
		return ;
	}

	Channel	&channel = _channels.find(target)->second;

	if (modeStr.empty())
	{
		std::string	modeParams;
		std::string	modes = buildCurrentModes(channel, modeParams);
		sendReply(fd, ":" + _name + RPL_CHANNELMODEIS + client.getNickname() + " " + target + " " + modes + modeParams);
		return ;
	}

	if (!channel.isAdmin(fd))
	{
		sendReply(fd, ":" + _name + ERR_CHANOPRIVSNEEDED + client.getNickname() + " " + target + " :You're not channel operator");
		return ;
	}

	std::vector<std::string>	args = parseArgs(modeArgs);
	size_t	argIdx = 0;
	bool	adding = true;
	char	lastSign = '\0';
	std::string	broadcastModes;
	std::string	broadcastArgs;

	for (size_t i = 0; i < modeStr.size(); i++)
	{
		char	c = modeStr[i];

		if (c == '+') { adding = true; continue ; }
		if (c == '-') { adding = false; continue ; }

		char	sign = adding ? '+' : '-';

		if (c == 'i')
		{
			channel.setInviteOnly(adding);
			if (sign != lastSign) { broadcastModes += sign; lastSign = sign; }
			broadcastModes += 'i';
		}
		else if (c == 't')
		{
			channel.setTopicRestricted(adding);
			if (sign != lastSign) { broadcastModes += sign; lastSign = sign; }
			broadcastModes += 't';
		}
		else if (c == 'k')
		{
			if (adding)
			{
				if (argIdx >= args.size())
				{
					sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " MODE :Not enough parameters");
					return ;
				}
				channel.setPasswordChannel(args[argIdx++]);
				broadcastArgs += " " + channel.getPasswordChannel();
			}
			else
				channel.setPasswordChannel("");
			if (sign != lastSign) { broadcastModes += sign; lastSign = sign; }
			broadcastModes += 'k';
		}
		else if (c == 'o')
		{
			if (argIdx >= args.size())
			{
				sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " MODE :Not enough parameters");
				return ;
			}
			const std::string	targetNick = args[argIdx++];
			int					targetFd = findFdByNick(_clients, targetNick);

			if (targetFd == -1 || !channel.hasMember(targetFd))
			{
				sendReply(fd, ":" + _name + ERR_USERNOTINCHANNEL + client.getNickname() + " " + targetNick + " " + target + " :They aren't on that channel");
				continue ;
			}
			if (adding)
				channel.addAdmin(targetFd);
			else
				channel.removeAdmin(targetFd);
			if (sign != lastSign) { broadcastModes += sign; lastSign = sign; }
			broadcastModes += 'o';
			broadcastArgs += " " + targetNick;
		}
		else if (c == 'l')
		{
			if (adding)
			{
				if (argIdx >= args.size())
				{
					sendReply(fd, ":" + _name + ERR_NEEDMOREPARAMS + client.getNickname() + " MODE :Not enough parameters");
					return ;
				}
				int	limit = std::atoi(args[argIdx++].c_str());
				channel.setLimit(limit > 0 ? limit : 0);
				std::ostringstream	ss;
				ss << channel.getUserLimit();
				broadcastArgs += " " + ss.str();
			}
			else
				channel.setLimit(0);
			if (sign != lastSign) { broadcastModes += sign; lastSign = sign; }
			broadcastModes += 'l';
		}
		else
		{
			sendReply(fd, ":" + _name + ERR_UNKNOWNMODE + client.getNickname() + " " + std::string(1, c) + " :is unknown mode char to me");
		}
	}

	if (!broadcastModes.empty())
	{
		const std::string	prefix = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname();
		channel.broadcast(prefix + " MODE " + target + " " + broadcastModes + broadcastArgs);
//		std::vector<int>	failed = channel.broadcast(prefix + " MODE " + target + " " + broadcastModes + broadcastArgs);
//		for (size_t i = 0; i < failed.size(); i++)
//			disconnectClient(failed[i]);
	}
}
