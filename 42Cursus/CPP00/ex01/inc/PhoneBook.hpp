/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:14:15 by smejia-a          #+#    #+#             */
/*   Updated: 2026/06/05 20:14:18 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
    private:
        Contact _agenda[8];
        int _old;

        /*Private functions*/
        void _printContact(int fields, int pos);
        std::string _trim(const std::string& str);
        void _printContactField(std::string field);

    public:
        /*Constructor*/
        PhoneBook(void);

        /*Destructor*/
        ~PhoneBook(void);

        /*Functions*/
        bool addContact(void);
        bool searchContact(void);
        void exit(void);
};

#endif

