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
    domain = isl_union_set_empty(isl_set_get_space(scop->context));
    pet = scop;
    computeRelationUnion();
    ctx = isl_union_set_get_ctx(domain);

    for (int i = 0; i < pet->n_stmt; i++)
    {
        struct pet_stmt* statement = pet->stmts[i];
        if (!pet_stmt_is_kill(statement))
        {
            isl_set* statement_domain = isl_set_copy(statement->domain);
            if (statement->n_arg > 0)
                statement_domain = isl_map_domain(isl_set_unwrap(statement_domain));
            domain = isl_union_set_add_set(domain, statement_domain);
        }
        else
        {
            const char* statement_label = isl_set_get_tuple_name(statement->domain);
            //schedule = remove_map_with_tuple(schedule, statement_label);
            //relation = remove_map_with_tuple(relation, statement_label);
        }
    }
    //schedule = simplify_schedule(schedule);//TODO: refactor to method
}
ScopInfo::~ScopInfo()
{
    //isl_union_map_free(reads);
    //isl_union_map_free(writes);
    //isl_union_map_free(schedule);
    //isl_union_map_free(relation);
    isl_union_set_free(domain);
    pet_scop_free(pet);
}
std::string ScopInfo::toString()
{
    std::stringstream s;
    s << "SCoPInfo: " << std::endl;

    s << "Domain: " << isl_union_set_to_str(domain) << std::endl;
    // s << "Schedule: " << isl_union_map_to_str(schedule) << std::endl;
    // s << "Relation: " << isl_union_map_to_str(relation) << std::endl;
    // s << "Reads:  " << isl_union_map_to_str(reads) << std::endl;
    // s << "Writes: " << isl_union_map_to_str(writes) << std::endl;
    return s.str();
}

void ScopInfo::computeRelationUnion() {
}

void ScopInfo::normalize()
{
}