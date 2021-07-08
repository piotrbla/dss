#include "fileutil.hh"

#include <assert.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>

std::string remove_extension(const std::string& path) {
    if (path == "." || path == "..")
        return path;
    size_t pos = path.find_last_of("\\/.");
    if (pos != std::string::npos && path[pos] == '.')
        return path.substr(0, pos);
    return path;
}

std::string dir_name_of(const std::string& name)
{
     size_t pos = name.find_last_of("\\/");
     return (std::string::npos == pos) ? "" : name.substr(0, pos);
}

void create_dir(const std::string& name)
{
    if (mkdir(name.c_str(), 0777) == -1)
        throw std::runtime_error("No rights to create directory or parent directory doesnt exists.");
}
