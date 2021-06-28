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
    isl_union_map_free(reads);
    isl_union_map_free(writes);
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
    s << "Schedule: " << isl_union_map_to_str(schedule) << std::endl;
    s << "Relation: " << isl_union_map_to_str(relation) << std::endl;
    s << "Reads:  " << isl_union_map_to_str(reads) << std::endl;
    s << "Writes: " << isl_union_map_to_str(writes) << std::endl;
    return s.str();
}
void computeFlow(
        __isl_keep isl_union_map* r1, __isl_keep isl_union_map* r2,
        __isl_keep isl_union_map* r3, __isl_keep isl_union_map* r4,
        __isl_keep isl_union_map **computed_rel)
{
    isl_union_map_compute_flow(isl_union_map_copy(r1), isl_union_map_copy(r2),
        isl_union_map_copy(r3), isl_union_map_copy(r4),
        NULL, computed_rel, NULL, NULL);

}

void ScopInfo::computeRelationUnion() {
    schedule = isl_schedule_get_map(pet->schedule);
    reads = pet_scop_get_may_reads(pet);
    writes = pet_scop_get_may_writes(pet);
    isl_space *space = isl_set_get_space(pet->context);
    isl_union_map *empty = isl_union_map_empty(space);

    isl_union_map *dep_read_after_write;
    isl_union_map *dep_write_after_read;
    isl_union_map *dep_write_after_write;

    computeFlow(reads, empty, writes, schedule, &dep_read_after_write);
    computeFlow(writes, empty, reads, schedule, &dep_write_after_read);
    computeFlow(writes, empty, writes, schedule, &dep_write_after_write);

    dep_read_after_write = isl_union_map_coalesce(dep_read_after_write);
    dep_write_after_read = isl_union_map_coalesce(dep_write_after_read);
    dep_write_after_write = isl_union_map_coalesce(dep_write_after_write);
    relation = dep_read_after_write;
    //    relation = isl_union_map_union(relation, dep_write_after_read);
    //   relation = isl_union_map_union(relation, dep_write_after_write);
    relation = isl_union_map_coalesce(relation);
    

    isl_union_map_free(empty);
    //relation = unwrap_range(relation);
}

void ScopInfo::normalize()
{
}