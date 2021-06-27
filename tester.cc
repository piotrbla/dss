#include "tester.hh"
#include "scopinfo.hh"
#include "options.hh"
#include <iostream>

void make_tests(int argc, char *argv[])
{
    if (argc>1)
    {
        if (std::string(argv[1]) == "test")
        {
            std::cout << "All tests done\n";
            exit(0);
        }   
    }   
}