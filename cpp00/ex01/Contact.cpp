/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:03:23 by alfsanch          #+#    #+#             */
/*   Updated: 2024/07/17 17:05:05 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
    : firstName(""), lastName(""), nickname(""), phoneNumber(""),
      darkestSecret("") {}

bool Contact::isEmpty() const 
{
  return firstName.empty() && lastName.empty() && nickname.empty() &&
         phoneNumber.empty() && darkestSecret.empty();
}

void Contact::setFirstName(const std::string &value) { firstName = value; }
void Contact::setLastName(const std::string &value) { lastName = value; }
void Contact::setNickname(const std::string &value) { nickname = value; }
void Contact::setPhoneNumber(const std::string &value) { phoneNumber = value; }
void Contact::setDarkestSecret(const std::string &value) {
  darkestSecret = value;
}

const std::string &Contact::getFirstName() const { return firstName; }
const std::string &Contact::getLastName() const { return lastName; }
const std::string &Contact::getNickname() const { return nickname; }
const std::string &Contact::getPhoneNumber() const { return phoneNumber; }
const std::string &Contact::getDarkestSecret() const { return darkestSecret; }
