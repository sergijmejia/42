#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>

class Fixed {
    private:
        int                 _numberValue;
        static const int    _fractionalBits = 8;

    public:
        /*Default Constructor*/
        Fixed();

        /*Copy Constructor*/
        Fixed(const Fixed& other);

        /*Copy assignment operator*/
        Fixed& operator= (const Fixed& other);

        /*Destructor*/
        ~Fixed();

        /*Getters*/
        int getRawBits(void) const;

        /*Setters*/
        void    setRawBits(int const raw);

        /*Paramatrized Constructors*/

        /*Members Functions*/
};

#endif