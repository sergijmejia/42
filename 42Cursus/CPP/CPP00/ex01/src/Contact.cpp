/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:14:36 by smejia-a          #+#    #+#             */
/*   Updated: 2026/06/05 20:15:52 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact(void) {
}

Contact::~Contact(void) {
}

void Contact::setFirstName(std::string str) {
    _firstName = str;
}

void Contact::setLastName(std::string str) {
    _lastName = str;
}

void Contact::setNickname(std::string str) {
    _nickname = str;
}

void Contact::setPhoneNumber(std::string str) {
    _phoneNumber = str;
}

void Contact::setDarkestSecret(std::string str) {
    _darkestSecret= str;
}

std::string Contact::getFirstName(void) {
    return _firstName;
}

std::string Contact::getLastName(void) {
    return _lastName;
}

std::string Contact::getNickname(void) {
    return _nickname;
}

std::string Contact::getPhoneNumber(void) {
    return _phoneNumber;
}

std::string Contact::getDarkestSecret(void) {
    return _darkestSecret;
}
