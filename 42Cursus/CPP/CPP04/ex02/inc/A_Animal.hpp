#ifndef A_ANIMAL_HPP
# define A_ANIMAL_HPP

# include <iostream>
# include <string>

class A_Animal {
    protected:
        std::string _type;

    public:
        A_Animal(void);
        A_Animal(std::string newType);
        A_Animal(const A_Animal& other);
        A_Animal& operator= (const A_Animal& other);
        virtual ~A_Animal(void);

        virtual std::string getType(void) const; 

        virtual void makeSound(void) const = 0; //Pure Virtual Function
};

#endif