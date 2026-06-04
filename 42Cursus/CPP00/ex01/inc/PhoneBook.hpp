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
        PhoneBook();

        /*Destructor*/
        ~PhoneBook();

        /*Functions*/
        bool addContact();
        bool searchContact();
        void exit();
};

#endif

