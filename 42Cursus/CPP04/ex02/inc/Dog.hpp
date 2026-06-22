#ifndef DOG_HPP
# define DOG_HPP

# include "A_Animal.hpp"
# include "Brain.hpp"

class Dog : public A_Animal {
    private:
        Brain* _brain;
    public:
        Dog(void);
        Dog(const Dog& other);
        Dog& operator= (const Dog& other);
        virtual ~Dog(void);

        virtual void makeSound(void) const;
};

#endif