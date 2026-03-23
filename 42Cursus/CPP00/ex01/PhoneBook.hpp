class PhoneBook {
    private:
        Contact agenda[8];
        int old = -1;

    public:
        void add();
        void search();
        void exit();
};

class Contact {
    private:
        std::string _firstName;
        std::string _lastName;
        std::string _nickname;
        std::string _phoneNumber;
        std::string _darkestSecret;

    public:
        void newContact();
        std::string getFirtsName();
        std::string getLastName();
        std::string getNickname();
};