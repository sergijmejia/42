#include "Harl.hpp"

int main(void) {
    Harl harl;

    std::cout << "--- TEST 1: Checking DEBUG ---" << std::endl;
    harl.complain("DEBUG");
    std::cout << std::endl;

    std::cout << "--- TEST 2: Checking INFO ---" << std::endl;
    harl.complain("INFO");
    std::cout << std::endl;

    std::cout << "--- TEST 3: Checking WARNING ---" << std::endl;
    harl.complain("WARNING");
    std::cout << std::endl;

    std::cout << "--- TEST 4: Checking ERROR ---" << std::endl;
    harl.complain("ERROR");
    std::cout << std::endl;

    std::cout << "--- TEST 5: Checking Edge cases ---" << std::endl;
    std::cout << "'UNKNOWN' as imput:" << std::endl;
    harl.complain("UNKNOWN");
    
    std::cout << "\n'debug' as imput (lowcase):" << std::endl;
    harl.complain("debug");
    std::cout << std::endl;

    return 0;
}
