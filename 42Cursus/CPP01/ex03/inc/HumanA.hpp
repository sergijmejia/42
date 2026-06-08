#ifndef HUMANA_HPP
# define HUMANA_HPP

# include "Weapon.hpp"

class HumanA {
    private:
        Weapon &_weaponA;
        std::string _name;

    public:
        HumanA(const std::string& newName, Weapon& newWeapon);
        
        ~HumanA(void);

        void setName(const std::string& newName);

        const Weapon&   getWeapon(void) const;
        const std::string&  getName(void) const;

        void    attack(void) const;
};

#endif