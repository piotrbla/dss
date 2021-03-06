#ifndef SCOPINFO_H
#define SCOPINFO_H

#include <isl/ctx.h>
#include <isl/set.h>
#include <isl/union_set.h>
#include <isl/union_map.h>
#include <pet.h>
#include "options.hh"

#include <string>

class ScopInfo
{
public:
    ScopInfo(pet_scop *scop);

    ~ScopInfo();
    std::string toString();
    void normalize();
    void print_code (std::string);
    void put_info_to_output_files(std::string );
private:
    isl_ctx* ctx;
    isl_union_set* domain;
    isl_union_map* schedule;
    isl_union_map* relation;
    isl_union_map* reads;
    isl_union_map* writes;
    pet_scop* pet;
    std::string macros_str;
    std::string wavefront_str;
    struct tc_options* options;
    void computeRelationUnion();
    void print_code_tc();
    void print_test_schedule();
    void print_test_union_set();
    void print_test_union_map();
};

#endif
