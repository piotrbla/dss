#include "scopinfo.hh"
#include "options.hh"
#include "fileutil.hh"
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
#include <isl/schedule.h>

#include "fileutil.hh"


void ScopInfo::print_code_tc()
{
    ;
}
 void ScopInfo::print_test_schedule()
 {
    isl_schedule * sched = isl_schedule_read_from_str(ctx, "{ domain: \"{ S_3[i] : 0 <= i <= 9; S_0[]; S_2[i] : 0 <= i <= 9; S_4[];  S_1[i] : 0 <= i <= 9 }\", child: { sequence: [ { filter: \"{ S_0[] }\" }, { filter:  \"{ S_3[i]; S_2[i]; S_1[i] }\", child: { schedule: \"L_0[{ S_2[i] -> [(i)]; S_3[i] -> [(i)]; S_1[i] -> [(i)] }]\", child: { sequence: [ { filter: \"{ S_1[i] }\" }, {  filter: \"{ S_2[i] }\" }, { filter: \"{ S_3[i] }\" } ] } } }, { filter: \"{ S_4[] }\"  } ] } }");
    //"[l, i, k] -> [(l, t = i - k)] }");
    std::cout <<  isl_schedule_to_str(sched);
 }

 void ScopInfo::print_test_basic_set()
 {
     ;
 }
 
 void ScopInfo::print_test_union_map()
 {
     ;
 }

void ScopInfo::print_code()
{
    print_test_schedule();
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
isl_union_map *computeFlow(
        __isl_keep isl_union_map* r1, __isl_keep isl_union_map* r2,
        __isl_keep isl_union_map* before)
{
    return isl_union_map_coalesce(isl_union_map_intersect(
					isl_union_map_apply_range(isl_union_map_copy(r1),
                    isl_union_map_reverse(isl_union_map_copy(r2))),
					isl_union_map_copy(before)));
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
	isl_union_map * before = isl_union_map_lex_lt_union_map(isl_union_map_copy(schedule), isl_union_map_copy(schedule));

    dep_read_after_write = computeFlow(writes, reads, before);
    dep_write_after_read = computeFlow(reads, writes, before);
    dep_write_after_write = computeFlow(writes, writes, before);
    relation = dep_read_after_write;
    //relation = dep_write_after_read;
    //    relation = isl_union_map_union(relation, dep_write_after_read);
    //   relation = isl_union_map_union(relation, dep_write_after_write);
    relation = isl_union_map_coalesce(relation);
    
    isl_union_map_free(empty);
    //relation = unwrap_range(relation);
}

void ScopInfo::put_info_to_output_files(std::string filename)
{
    std::string dir_name = dir_name_of(filename);
    if(dir_name == "")
        dir_name.append(".");
    dir_name.append("/output/");
    create_dir(dir_name);
    std::string base_name = remove_extension(base_file_name(filename));
    std::string base_output_path = dir_name + base_name;
    write_string_to_file(base_output_path + ".domain", "Domain", isl_union_set_to_str(domain));
    write_string_to_file(base_output_path + ".schedule", "Schedule", isl_union_map_to_str(schedule));
    write_string_to_file(base_output_path + ".relation", "Relation", isl_union_map_to_str(relation));
    write_string_to_file(base_output_path + ".reads", "Reads", isl_union_map_to_str(reads));
    write_string_to_file(base_output_path + ".writes", "Writes", isl_union_map_to_str(writes));
 }
    

void ScopInfo::normalize()
{
}