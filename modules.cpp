// Main program file: main.cpp
#include <iostream>
import math_module;

int main() {
    int result1 = math::add(10, 5);
    int result2 = math::subtract(10, 5);
    
    std::cout << "Addition result: " << result1 << std::endl;
    std::cout << "Subtraction result: " << result2 << std::endl;

    return 0;
}
