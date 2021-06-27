#include "tester.hh"
#include "scopinfo.hh"
#include "options.hh"
#include "fileutil.hh"
#include <iostream>
#include <assert.h>

void test_remove_extension()
{
    assert(remove_extension("file.c")=="file");
    assert(remove_extension("bin/file.c")=="bin/file");   
    assert(remove_extension("bin.ary")=="bin");
    assert(remove_extension("p/foo.baz/bin.ary")=="p/foo.baz/bin");
    assert(remove_extension("p/foo.baz/binary")=="p/foo.baz/binary");
}

void make_tests(int argc, char *argv[])
{
    if (argc>1)
    {
        if (std::string(argv[1]) == "test")
        {
            test_remove_extension();
            std::cout << "All tests done\n";
            exit(0);
        }   
    }   
}