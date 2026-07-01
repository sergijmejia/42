#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <iostream>
# include <string>

class Weapon {
    private:
        std::string type;
    
    public:
        Weapon(void);
        Weapon(const std::string& newValue);

        ~Weapon(void);

        void setType(const std::string& newValue);

        const std::string& getType(void) const;
};

#endif