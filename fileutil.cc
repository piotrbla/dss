#include "fileutil.hh"
#include <iostream>
std::string remove_extension(const std::string& path) {
    if (path == "." || path == "..")
        return path;
    size_t pos = path.find_last_of("\\/.");
    if (pos != std::string::npos && path[pos] == '.')
        return path.substr(0, pos);
    return path;
}