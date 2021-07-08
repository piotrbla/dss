#include "fileutil.hh"

#include <assert.h>
#include <iostream>
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
