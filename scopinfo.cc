#include "scopinfo.hh"
#include "options.hh"
#include <sstream>
#include <cstring>
#include <iostream>
#include <isl/flow.h>
#include <isl/set.h>
#include <isl/ctx.h>
#include <isl/id.h>
#include <isl/set.h>
#include <isl/union_map.h>
#include <isl/union_set.h>

void ScopInfo::print_code_tc()
{
    ;
}
void ScopInfo::print_code()
{
    ;
}


ScopInfo::ScopInfo(pet_scop* scop)
{
}
ScopInfo::~ScopInfo()
{
    isl_union_map_free(reads);
    isl_union_map_free(writes);
    isl_union_map_free(schedule);
    isl_union_map_free(relation);
    isl_union_set_free(domain);
    pet_scop_free(pet);
}
std::string ScopInfo::toString()
{
    std::stringstream s;
    s << "SCoPInfo: " << std::endl;

    s << "Domain: " << isl_union_set_to_str(domain) << std::endl;
    s << "Schedule: " << isl_union_map_to_str(schedule) << std::endl;
    s << "Relation: " << isl_union_map_to_str(relation) << std::endl;
    s << "Reads:  " << isl_union_map_to_str(reads) << std::endl;
    s << "Writes: " << isl_union_map_to_str(writes) << std::endl;
    return s.str();
}

void ScopInfo::computeRelationUnion() {
}

void ScopInfo::normalize()
{
}