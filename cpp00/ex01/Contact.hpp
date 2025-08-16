#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
	public:
		Contact();
		bool isEmpty() const;
		void setFirstName(const std::string &value);
		void setLastName(const std::string &value);
		void setNickname(const std::string &value);
		void setPhoneNumber(const std::string &value);
		void setDarkestSecret(const std::string &value);
		const std::string &getFirstName() const;
		const std::string &getLastName() const;
		const std::string &getNickname() const;
		const std::string &getPhoneNumber() const;
		const std::string &getDarkestSecret() const;

	private:
		std::string firstName;
		std::string lastName;
		std::string nickname;
		std::string phoneNumber;
		std::string darkestSecret;
	};

#endif
