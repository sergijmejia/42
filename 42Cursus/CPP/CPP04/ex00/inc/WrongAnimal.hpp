#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal {
    protected:
        std::string _type;

    public:
        WrongAnimal(void);
        WrongAnimal(std::string newType);
        WrongAnimal(const WrongAnimal& other);
        WrongAnimal& operator= (const WrongAnimal& other);
        ~WrongAnimal(void);

        void makeSound(void) const;
};

#endif