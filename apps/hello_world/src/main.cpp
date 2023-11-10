#include <iostream>

#include "ProjectTemplate/configure.hpp"
#include "ProjectTemplate/hello.hpp"

int main()
{
        std::cout << "version: " << ProjectTemplate::version << std::endl;
        ProjectTemplate::hello();
        return 0;
}
