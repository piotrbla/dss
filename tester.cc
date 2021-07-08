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

void test_dir_name_of()
{
    std::cout << dir_name_of("bin/file.c") << "\n";
    assert(dir_name_of("file.c")=="");
    assert(dir_name_of("bin/file.c")=="bin");   
    assert(dir_name_of("bin.ary")=="");
    assert(dir_name_of("p/foo.baz/bin.ary")=="p/foo.baz");
    assert(dir_name_of("p/foo.baz/binary")=="p/foo.baz");
}

void make_tests(int argc, char *argv[])
{
    if (argc>1)
    {
        if (std::string(argv[1]) == "test")
        {
            test_remove_extension();
            test_dir_name_of();
            std::cout << "All tests done\n";
            exit(0);
        }   
    }   
}