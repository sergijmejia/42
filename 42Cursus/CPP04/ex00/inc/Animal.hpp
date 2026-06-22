#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal {
    protected:
        std::string _type;

    public:
        Animal(void);
        Animal(std::string newType);
        Animal(const Animal& other);
        Animal& operator= (const Animal& other);
        virtual ~Animal(void);

        virtual void makeSound(void) const;
};

#endif