#ifndef FILEUTIL_H
#define FILEUTIL_H
#include<iostream>
std::string remove_extension(const std::string& path) ;
std::string dir_name_of(const std::string& name);
void create_dir(const std::string& path);
#endif