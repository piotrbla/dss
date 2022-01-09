#include "scopinfo.hh"
#include "codegen.hh"
#include "options.hh"
#include "fileutil.hh"
#include "loop_scop.hh"
#include "dapt_params.hh"
#include "tool_isl.hh"
#include "tool_debug.hh"
#include <sstream>
#include <cstring>
#include <string>
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
    std::cout <<  isl_schedule_to_str(sched) << "\n";
 }

 void ScopInfo::print_test_union_set()
 {
     isl_union_set * s = isl_union_set_read_from_str(ctx, "{ B [0]; A[2 ,8 ,1] }");
     std::cout << isl_union_set_to_str(s)<< "\n";
 }
 
 void ScopInfo::print_test_union_map()
 {
     isl_union_map * m1 = isl_union_map_read_from_str(ctx, "{A[2, 8, 1] -> B[5]; A[2, 8, 1] -> B[6]; B[5] -> B[5] }");
      std::cout << isl_union_map_to_str(m1)<< "\n";
     isl_union_map * m2 = isl_union_map_read_from_str(ctx, "{[l, i, k]->[l, i, k]}");
     std::cout << isl_union_map_to_str(m2)<< "\n";
     isl_union_map * m3 = isl_union_map_read_from_str(ctx, "{[l, i, k]->[l, t=i - k]}");
     std::cout << isl_union_map_to_str(m3)<< "\n";
     isl_union_map * m4 = isl_union_map_read_from_str(ctx, "{S_0[l, i, k]->S_0[l, t=i - k]}");
     std::cout << isl_union_map_to_str(m4)<< "\n";
}

void ScopInfo::print_code(std::string schedule_string)
{
    //print_test_schedule();
    //print_test_union_set();
    //print_test_union_map();
    dapt_params daptParams;
    pet_options_set_signed_overflow(ctx, PET_OVERFLOW_IGNORE);
    isl_options_set_ast_iterator_type(ctx, daptParams.iteratortype);
    pet_scop *petScop = pet;
    if(petScop != 0)
    {
        loop_scop *loopScop = loop_scop_extract_from_pet_scop(petScop, &daptParams);
        // FILE *mapFile = fopen(daptParams.mapfile,"rt");
        //isl_union_map *schedule = isl_union_map_read_from_file(ctx, mapFile);
        //fclose(mapFile);
        //isl_union_map * new_schedule = isl_union_map_read_from_str(ctx, "{S_0[l, i, k]->S_0[l, t=i - k]}");
        isl_union_map * new_schedule = isl_union_map_read_from_str(ctx, schedule_string.c_str());
        loop_scop_from_pet_debug_printf(loopScop);
        std::cout << "Schedule before: " << isl_union_map_to_str(new_schedule)<< "\n";
        new_schedule = isl_union_map_intersect_domain(new_schedule, isl_union_set_copy(loopScop->loopDomain));
        std::cout << "Schedule  after: " << isl_union_map_to_str(new_schedule)<< "\n";
        std::cout << "Domain: " << isl_union_set_to_str(loopScop->loopDomain)<< "\n";
        isl_debug_printf("\n#%s\n", "######################################################################");
        isl_debug_printf_union_map("\n#schedule code: %s\n", new_schedule);
        isl_debug_printf("\n#%s\n", "######################################################################");

        loop_scop_check_schedule_respects_deps(loopScop, new_schedule);

        if (daptParams.dapt_respects_deps == isl_bool_false)//TODO: change
        {
            isl_printf_str("\n//dapt code:\n%s", codegen_macros_to_str(new_schedule, petScop));
            isl_printf_str("%s", codegen_wavefront_to_str(new_schedule, petScop, 0, isl_bool_false));
        }
        else
        {
            std::cout<< "Error\n"; 
            //isl_printf_str("\n//dapt code:\n%s", "//Error: see debug info");
        }
        loopScop = loop_scop_loop_scop_free(loopScop);
        new_schedule = isl_union_map_free(new_schedule);
    }
}

ScopInfo::ScopInfo(pet_scop *scop)
{
    domain = isl_union_set_empty(isl_set_get_space(scop->context));
    pet = scop;
    computeRelationUnion();
    ctx = isl_union_set_get_ctx(domain);

    for (int i = 0; i < pet->n_stmt; i++)
    {
        struct pet_stmt *statement = pet->stmts[i];
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