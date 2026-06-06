#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie {
    private:
        /*Data Members*/
        std::string _name;

    public:
        /*Constructor*/
        Zombie(void);

        /*Destructor*/
        ~Zombie(void);

        /*Setters*/
        void    setName(std::string zombieName);

        /*Getters*/
        std::string getName(void);

        /*Member Functions*/
        void    announce(void);
};

Zombie* zombieHorde(int N, std::string name);


#endif