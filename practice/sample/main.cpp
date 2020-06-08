#include <iostream>
#include "a.hpp"

int main()
{
    c c1;
    c1.set(100);
    std::cout << c1.get() << "\n" << std::endl;

    return 0;
}