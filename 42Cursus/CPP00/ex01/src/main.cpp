/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:24:22 by smejia-a          #+#    #+#             */
/*   Updated: 2026/06/05 20:24:25 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

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
