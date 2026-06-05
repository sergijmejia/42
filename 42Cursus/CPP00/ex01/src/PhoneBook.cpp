/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:16:13 by smejia-a          #+#    #+#             */
/*   Updated: 2026/06/05 20:19:21 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <sstream>
#include <cstdlib>

PhoneBook::PhoneBook(void) {
    _old = 0;
}

PhoneBook::~PhoneBook(void) {
}

void PhoneBook::_printContact(int fields, int pos){
    if (fields >= 1)
        std::cout << _agenda[pos].getFirstName() << std::endl;
    if (fields >= 2)
        std::cout << _agenda[pos].getLastName() << std::endl;
    if (fields >= 3)
        std::cout << _agenda[pos].getNickname() << std::endl;
    if (fields >= 4)
        std::cout << _agenda[pos].getPhoneNumber() << std::endl;
    if (fields >= 5)
        std::cout << _agenda[pos].getDarkestSecret() << std::endl;
}

std::string PhoneBook::_trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos)
        return "";
    return str.substr(start, end - start + 1);
}

void PhoneBook::_printContactField(std::string field){
    int l = field.length();

    if (l <= 10){
        l++;
        while (l <= 10){
            std::cout << " ";
            l++;
        }
        std::cout << field;
    }
    else
        std::cout << field.substr(0,9) << ".";
    std::cout << "|";
}

bool PhoneBook::addContact(void) {
    std::string newData;
    
    for (int i = 0; i < 5; i++){
        switch(i){
            case 0:
                std::cout << "Name ";
                break;
            case 1:
                std::cout <<"Last name ";
                break;
            case 2:
                std::cout << "Nickname ";
                break;
            case 3:
                std::cout << "Phone number ";
                break; 
            case 4:
                std::cout << "Darkest secret ";
                break;
        }
        std::cout << "of the new contact: ";
        std::getline(std::cin, newData);
        if (std::cin.eof()) {
        	std::exit(0);
        }
        newData = _trim(newData);
        if (newData.empty()){
            std::cout << std::endl << "This field can't be empty, please try again" << std::endl << std::endl;
            i--;
            continue;
        }
        else if (std::cin.eof())
            return(false);
        switch(i){
            case 0:
                _agenda[_old].setFirstName(newData);
                break;
            case 1:
                _agenda[_old].setLastName(newData);
                break;
            case 2:
                _agenda[_old].setNickname(newData);
                break;
            case 3:
                _agenda[_old].setPhoneNumber(newData);
                break;
            case 4:
                _agenda[_old].setDarkestSecret(newData);
                break;
        }
    }
    _old++;
    if (_old == 8)
        _old = 0;
    
    return (true);
}    

bool PhoneBook::searchContact(void){
    int i = 0;
    int l;
    std::string index;

    while (i < 8 && !_agenda[i].getFirstName().empty()){
        std::cout<< "|       " << i + 1 << "|";
        _printContactField(_agenda[i].getFirstName());
        _printContactField(_agenda[i].getLastName());
        _printContactField(_agenda[i].getNickname());
        std::cout << std::endl;
        i++;
    }
    if (i == 0){
        std::cout << "There are no contacts yet, please add one" << std::endl;
        return (true);
    }
    while (true){
        std::cout << std::endl << "Select index to display contact information: ";
        std::getline(std::cin, index);
        if (std::cin.eof()) {
        	std::exit(0);
        }
        std::stringstream conversor(index);
        conversor >> l;
        if (l < 1 || l > i)
            std::cout << std::endl << "That index doesn't exist, please try again" << std::endl;
        else
            break;
    }
    std::cout << std::endl;
    _printContact(5, l - 1);
    return (true);
}

void PhoneBook::exit(void){
    std::cout << "Good bye!" << std::endl;
}
