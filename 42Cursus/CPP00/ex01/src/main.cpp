#include "PhoneBook.hpp"
#include <iostream>

int main() {
    PhoneBook phoneBook;
    std::string command;

    while (std::cout << "Enter command (ADD, SEARCH, EXIT): " && std::getline(std::cin, command)) {
        if (command == "ADD") {
            std::cout << std::endl;
            phoneBook.addContact();
            std::cout << std::endl;
        } 
        else if (command == "SEARCH") {
            std::cout << std::endl;
            phoneBook.searchContact();
            std::cout << std::endl;
        } 
        else if (command == "EXIT") {
            std::cout << std::endl;
            phoneBook.exit();
            break;
        } 
        else {
            std::cout << std::endl;
            std::cout << "Invalid command." << std::endl;
            std::cout << std::endl;
        }
    }
    return 0;
}