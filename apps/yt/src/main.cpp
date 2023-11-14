#include <iostream>

#include "yt/configure.hpp"
#include "yt/hello.hpp"

int main()
{
        std::cout << "version: " << yt::version << std::endl;
        yt::hello();
        return 0;
}
