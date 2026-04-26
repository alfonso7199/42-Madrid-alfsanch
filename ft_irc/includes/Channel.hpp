#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <map>
# include <set>
# include <vector>
# include "Client.hpp"

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::string				_passwordChannel;
		int						_userlimit;
		bool					_inviteOnly;
		bool					_topicRestricted;
		std::map<int, Client *>	_members;
		std::set<int>			_admins;
		std::set<int>			_invited;

	public:
		Channel(const std::string &name);
		Channel(const Channel &other);
		Channel	&operator=(const Channel &other);
		~Channel(void);

		const std::string			&getName(void) const;
		const std::string			&getTopic(void) const;
		const std::string			&getPasswordChannel(void) const;
		int							getUserLimit(void) const;
		bool						isInviteOnly(void) const;
		bool						isTopicRestricted(void) const;
		int							getMemberCount(void) const;
		std::map<int, Client *>		&getMembers(void);

		void	setTopic(const std::string &topic);
		void	setPasswordChannel(const std::string &key);
		void	setLimit(int limit);
		void	setInviteOnly(bool val);
		void	setTopicRestricted(bool val);

		void	addMember(Client *client);
		void	removeMember(int fd);
		bool	hasMember(int fd) const;

		void	addAdmin(int fd);
		void	removeAdmin(int fd);
		bool	isAdmin(int fd) const;

		void	addInvited(int fd);
		void	removeInvited(int fd);
		bool	isInvited(int fd) const;

		void	broadcast(const std::string &msg, int excludeFd = -1) const;
};

#endif
