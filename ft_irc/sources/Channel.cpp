#include "Channel.hpp"

Channel::Channel(const std::string &name) :
_name(name), _topic(""), _passwordChannel(""), _userlimit(0),
_inviteOnly(false), _topicRestricted(false)
{
	return ;
}

Channel::Channel(const Channel &other) :
_name(other._name), _topic(other._topic), _passwordChannel(other._passwordChannel),
_userlimit(other._userlimit), _inviteOnly(other._inviteOnly),
_topicRestricted(other._topicRestricted), _members(other._members),
_admins(other._admins), _invited(other._invited)
{
	return ;
}

Channel	&Channel::operator=(const Channel &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_topic = other._topic;
		this->_passwordChannel = other._passwordChannel;
		this->_userlimit = other._userlimit;
		this->_inviteOnly = other._inviteOnly;
		this->_topicRestricted = other._topicRestricted;
		this->_members = other._members;
		this->_admins = other._admins;
		this->_invited = other._invited;
	}
	return (*this);
}

Channel::~Channel(void)
{
	return ;
}

const std::string	&Channel::getName(void) const
{
	return (this->_name);
}

const std::string	&Channel::getTopic(void) const
{
	return (this->_topic);
}

const std::string	&Channel::getPasswordChannel(void) const
{
	return (this->_passwordChannel);
}

int	Channel::getUserLimit(void) const
{
	return (this->_userlimit);
}

bool	Channel::isInviteOnly(void) const
{
	return (this->_inviteOnly);
}

bool	Channel::isTopicRestricted(void) const
{
	return (this->_topicRestricted);
}

int	Channel::getMemberCount(void) const
{
	return (this->_members.size());
}

std::map<int, Client *>	&Channel::getMembers(void)
{
	return (this->_members);
}

void	Channel::setTopic(const std::string &topic)
{
	this->_topic = topic;
}

void	Channel::setPasswordChannel(const std::string &key)
{
	this->_passwordChannel = key;
}

void	Channel::setLimit(int limit)
{
	this->_userlimit = limit;
}

void	Channel::setInviteOnly(bool val)
{
	this->_inviteOnly = val;
}

void	Channel::setTopicRestricted(bool val)
{
	this->_topicRestricted = val;
}

void	Channel::addMember(Client *client)
{
	this->_members[client->getFd()] = client;
}

void	Channel::removeMember(int fd)
{
	this->_members.erase(fd);
	this->_admins.erase(fd);
	this->_invited.erase(fd);
}

bool	Channel::hasMember(int fd) const
{
	return (this->_members.count(fd) > 0);
}

void	Channel::addAdmin(int fd)
{
	this->_admins.insert(fd);
}

void	Channel::removeAdmin(int fd)
{
	this->_admins.erase(fd);
}

bool	Channel::isAdmin(int fd) const
{
	return (this->_admins.count(fd) > 0);
}

void	Channel::addInvited(int fd)
{
	this->_invited.insert(fd);
}

void	Channel::removeInvited(int fd)
{
	this->_invited.erase(fd);
}

bool	Channel::isInvited(int fd) const
{
	return (this->_invited.count(fd) > 0);
}

void	Channel::broadcast(const std::string &msg, int excludeFd) const
{
	for (std::map<int, Client *>::const_iterator it = _members.begin();
		it != _members.end(); ++it)
		{
			if (it->first != excludeFd)
				it->second->queueOut(msg);
		}
}
