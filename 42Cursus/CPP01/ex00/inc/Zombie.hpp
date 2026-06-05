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
        Zombie( void );

        /*Destructor*/
        ~Zombie( void );

        /*Setters*/
        void    setName(std::string zombieName);

        /*Member Functions*/
        void    announce( void );
}


#ENDIF