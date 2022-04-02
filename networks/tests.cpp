#include <iostream>
#include <string>

#include "config.h"

/*
    Using information gathered from:

        https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive

    which references the more general information from:

        https://sourceforge.net/p/predef/wiki/OperatingSystems/
*/
#if defined(__APPLE__) || defined(__MACH__)
    #define OS_NAME "MacOS"
#elif defined(__linux__)
    #define OS_NAME "Linux"
#elif defined(_WIN32)
    #define OS_NAME "Windows"
#else
    #error "Unale to determine the Operating System Type"
#endif

int main(int argc, char **argv) {
    std::cout << "Running tests\n";
    for(int idx = 0 ;  idx < argc ; idx++)
        std::cout << "Parameter: " << idx << " is " << argv[idx] << std::endl;
    std::cout << "Operating System: " << OS_NAME << std::endl;
    return 1;
}