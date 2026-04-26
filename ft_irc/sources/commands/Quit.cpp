#include "Server.hpp"

void	Server::cmdQuit(int fd, const std::string &params)
{
	std::string	reason = "Quit";

	if (!params.empty())
	{
		if (params[0] == ':')
			reason = params.substr(1);
		else
			reason = params;
	}

	disconnectClient(fd, reason);
}
