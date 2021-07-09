#ifndef FILEUTIL_H
#define FILEUTIL_H
#include<iostream>
std::string remove_extension(const std::string& path) ;
std::string dir_name_of(const std::string& name);
void create_dir(const std::string& path);
std::string base_file_name(const std::string& path);
void write_string_to_file(const std::string& filename, const std::string& header_string, const std::string& info_string);
#endif