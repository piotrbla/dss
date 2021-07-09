#include "fileutil.hh"

#include <assert.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <exception>
#include <fstream>

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
    struct stat st = {0};
    if (stat(name.c_str(), &st) != -1) 
        return;
    if (mkdir(name.c_str(), 0777) == -1)
        throw std::runtime_error("No rights to create directory or parent directory doesnt exists.");
}

std::string base_file_name(const std::string& path)
{
  return path.substr(path.find_last_of("/\\") + 1);
}


void write_string_to_file(const std::string& filename, const std::string& header_string, const std::string& info_string)
{
    std::ofstream file_out(filename);
    if(!file_out.is_open())
        throw std::runtime_error("Error opening file " + filename );
    file_out << header_string << ": " << info_string << "\n";
    file_out.close();

}