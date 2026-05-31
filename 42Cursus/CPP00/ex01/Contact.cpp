#include "Contact.hpp"
#include <iostream>
#include <string>

Contact::Contact(){
}

Contact::~Contact(){
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

std::string Contact::getFirstName(){
    return _firstName;
}

std::string Contact::getLastName(){
    return _lastName;
}

std::string Contact::getNickname(){
    return _nickname;
}

std::string Contact::getPhoneNumber(){
    return _phoneNumber;
}

std::string Contact::getDarkestSecret(){
    return _darkestSecret;
}