#include "Point.hpp"

// Function prototype
bool bsp(Point const a, Point const b, Point const c, Point const point);

void printResult(std::string testName, bool expected, bool result) {
    std::cout << testName << ": ";
    if (expected == result)
        std::cout << "\033[32m[OK]\033[0m"; // Green
    else
        std::cout << "\033[31m[KO]\033[0m"; // Red
    std::cout << " (Expected " << expected << ", returned " << result << ")" << std::endl;
}

int main(void) {
    // Define our test triangle
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(0.0f, 10.0f);

    std::cout << "--- STARTING BSP TEST SUITE ---" << std::endl;

    // 1. Point clearly inside
    Point pInside(2.0f, 2.0f);
    printResult("1. Inside Point (2, 2)         ", true, bsp(a, b, c, pInside));

    // 2. Point clearly outside
    Point pOutside(10.0f, 10.0f);
    printResult("2. Outside Point (10, 10)      ", false, bsp(a, b, c, pOutside));

    // 3. Point exactly on the edge AB (PDF requires False)
    Point pEdge(5.0f, 0.0f);
    printResult("3. Point on edge AB (5, 0)     ", false, bsp(a, b, c, pEdge));

    // 4. Point exactly on the hypotenuse edge BC
    Point pHypotenuse(5.0f, 5.0f);
    printResult("4. Point on edge BC (5, 5)     ", false, bsp(a, b, c, pHypotenuse));

    // 5. Point exactly on vertex A (PDF requires False)
    Point pVertex(0.0f, 0.0f);
    printResult("5. Point on vertex A (0, 0)    ", false, bsp(a, b, c, pVertex));

    // 6. Outside point very close to the edge (Fixed precision test)
    Point pClose(-0.01f, 2.0f);
    printResult("6. Close outside (-0.01, 2)    ", false, bsp(a, b, c, pClose));

    std::cout << "-------------------------------" << std::endl;

    return 0;
}