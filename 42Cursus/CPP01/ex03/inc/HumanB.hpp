#ifndef HUMANB_HPP
# define HUMANB_HPP

# include "Weapon.hpp"

class HumanB {
    private:
        Weapon* _weaponB;
        std::string _name;

    public:
        HumanB(void);
        HumanB(const std::string& newName);
        
        ~HumanB(void);

        void setName(const std::string& newName);
        void setWeapon(Weapon& newWeapon);

        Weapon* getWeapon(void) const;
        const std::string&  getName(void) const;

        void    attack(void) const;
};

#endif