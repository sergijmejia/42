#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook {
    private:
        Contact _agenda[8];
        int _old;

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

