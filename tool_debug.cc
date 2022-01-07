/*
 * tool_debug.c
 *
 *  Created on: May 15, 2020
 *
 */

#include "tool_debug.hh"

static int print_debug_info = 0;

void isl_debug_on(){
	print_debug_info = -1;
}

int isl_debug_is_on(){
	return print_debug_info;
}

int isl_debug_printf(const char* format_template, const char* str){
	int result = 0;
	if(print_debug_info)
		result = fprintf(stderr, format_template,str);
	return result;
}

int isl_debug_printf_int(const char* format_template, int val){
	int result = 0;
	if(print_debug_info)
		result = fprintf(stderr, format_template,val);
	return result;
}

int isl_debug_printf_str(const char* format_template, __isl_take char* isl_str){
	int result = 0;

	if(print_debug_info)
		result = fprintf(stderr,format_template, isl_str);
	free(isl_str);

	return result;
}

int isl_debug_printf_union_set(const char* format_template, __isl_keep isl_union_set* uset){
	int result = 0;
	if(print_debug_info)
		result = isl_debug_printf_str(format_template, isl_union_set_to_str(uset));
	return result;
}
int isl_debug_printf_union_map(const char* format_template, __isl_keep isl_union_map* umap){
	int result = 0;
	if(print_debug_info)
		result = isl_debug_printf_str(format_template, isl_union_map_to_str(umap));
	return result;
}

int isl_debug_printf_set(const char* format_template, __isl_keep isl_set* set){
	int result = 0;
	if(print_debug_info)
		result = isl_debug_printf_str(format_template, isl_set_to_str(set));
	return result;
}
int isl_debug_printf_map(const char* format_template, __isl_keep isl_map* map){
	int result = 0;
	if(print_debug_info)
		result = isl_debug_printf_str(format_template, isl_map_to_str(map));
	return result;
}

int isl_debug_printf_schedule(const char* format_template, __isl_keep isl_schedule* sched){
	int result = 0;
	if(print_debug_info)
		result = isl_debug_printf_str(format_template, isl_schedule_to_str(sched));
	return result;
}

