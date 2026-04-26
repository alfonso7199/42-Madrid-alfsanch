#include "Server.hpp"

void	Server::disconnectClient(int fd, const std::string &reason)
{
	std::map<int, Client>::iterator	clientIt = _clients.find(fd);
	if (clientIt == _clients.end())
		return ;

	Client		&client = clientIt->second;
	std::string	quitMsg = ":" + client.getNickname() + "!" + client.getUsername() + "@" + client.getHostname() + " QUIT :" + reason;

	std::vector<std::string>	chanNames;
	for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second.hasMember(fd))
			chanNames.push_back(it->first);
	}

	for (size_t n = 0; n < chanNames.size(); n++)
	{
		if (!_channels.count(chanNames[n]))
			continue ;
		Channel	&chan = _channels.find(chanNames[n])->second;
		if (!chan.hasMember(fd))
			continue ;
		chan.broadcast(quitMsg, fd);
//		std::vector<int>	failed = chan.broadcast(quitMsg, fd);
//		for (size_t i = 0; i < failed.size(); i++)
//			disconnectClient(failed[i]);
		if (!_channels.count(chanNames[n]))
			continue ;
		Channel	&chan2 = _channels.find(chanNames[n])->second;
		chan2.removeMember(fd);
		if (chan2.getMemberCount() == 0)
			_channels.erase(chanNames[n]);
	}

	for (size_t i = 0; i < _pollfds.size(); i++)
	{
		if (_pollfds[i].fd == fd)
		{
			_pollfds.erase(_pollfds.begin() + i);
			break ;
		}
	}

	close(fd);
	_clients.erase(fd);
}
