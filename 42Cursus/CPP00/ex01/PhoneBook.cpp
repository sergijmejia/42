#include "PhoneBook.hpp"
#include <iostream>
#include <string>
#include <sstream>

PhoneBook::PhoneBook(){
    _old = 0;
}

PhoneBook::~PhoneBook(){
}

bool PhoneBook::addContact() {
    std::string newData;
    
    for (int i = 0; i < 5; i++){
        switch(i){
            case 0:
                std::cout << "Name ";
            case 1:
                std::cout <<"Last name ";
            case 2:
                std::cout << "Nickname ";
            case 3:
                std::cout << "Phone number ";
            case 4:
                std::cout << "Darkest secret ";
        }
        std::cout << "of de new contact: ";
        std::getline(std::cin, newData);
        if (std::cin.eof())
            return(false);
        std::cout << std::endl;
        switch(i){
                _agenda[_old].setFirstName(newData);
            case 1:
                _agenda[_old].setLastName(newData);
            case 2:
                _agenda[_old].setNickname(newData);
            case 3:
                _agenda[_old].setPhoneNumber(newData);
            case 4:
                _agenda[_old].setDarkestSecret(newData);
        }
    }
    _old++;
    if (_old == 8)
        _old = 0;
    
    return (true);
}    

bool PhoneBook::searchContact(){
    int i = 0;
    int l;
    std::string index;

    while (i < 10 && !_agenda[i].getFirstName().empty()){
        if (i < 9)
            std::cout << " " << i << "|";
        else
            std::cout << "10|";
        l = _agenda[i].getFirstName().length();
        if (l <= 10){
            l++;
            while (l <= 10){
                std::cout << " ";
                l++;
            }
            std::cout << _agenda[i].getFirstName();
        }
        else
            std::cout << _agenda[i].getFirstName().substr(0,9) << ".";
        std::cout << "|";
        l = _agenda[i].getLastName().length();
        if (l <= 10){
            l++;
            while (l <= 10){
                std::cout << " ";
                l++;
            }
            std::cout << _agenda[i].getLastName();
        }
        else
            std::cout << _agenda[i].getLastName().substr(0,9) << ".";
        std::cout << "|";
        l = _agenda[i].getNickname().length();
        if (l <= 10){
            l++;
            while (l <= 10){
                std::cout << " ";
                l++;
            }
            std::cout << _agenda[i].getNickname();
        }
        else
            std::cout << _agenda[i].getNickname().substr(0,9) << ".";
        std::cout << std::endl;
        i++;
    }
    while (true){
    std::cout << "Select index to display contact information " << std::endl;
    std::getline(std::cin, index);
    std::stringstream conversor(index);
    conversor >> l;
        if (l < 1 || l > i)
            std::cout << "That index doesn't exist, please try again" << std::endl;
        else
            break;
    }
    std::cout << _agenda[i].getFirstName() << std::endl;
    std::cout << _agenda[i].getLastName() << std::endl;
    std::cout << _agenda[i].getNickname() << std::endl;
    std::cout << _agenda[i].getPhoneNumber() << std::endl;
    std::cout << _agenda[i].getDarkestSecret() << std::endl;
}
