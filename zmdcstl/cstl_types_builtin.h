#ifndef _CSTL_TYPES_BUILTIN_H_
#define _CSTL_TYPES_BUILTIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/* default copy, less, and destroy function */
extern void _type_init_default(const void* cpv_input, void* pv_output);
extern void _type_copy_default(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_default(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_default(const void* cpv_input, void* pv_output);

/**
 * The cstl builtin copy, compare destroy function for c builtin type and cstl builtins.
 * @param cpv_input    input parameter.
 * @param cpv_first    first input parameter.
 * @param cpv_second   second input parameter.
 * @param pv_output    output parameter.
 * @return void.
 * @remarks cpv_input, cpv_first, cpv_second and pv_output must not be NULL.
 */
/* c builtin */
/* char */
#define declare_type_less_ctype(type) \
extern int _type_less_##type(void* cpv_first, void* cpv_second);

declare_type_less_ctype(int8_t);
declare_type_less_ctype(uint8_t);
declare_type_less_ctype(int16_t);
declare_type_less_ctype(uint16_t);
declare_type_less_ctype(int32_t);
declare_type_less_ctype(uint32_t);
declare_type_less_ctype(int64_t);
declare_type_less_ctype(uint64_t);
declare_type_less_ctype(float);
declare_type_less_ctype(double);
extern int _type_less_pointer(void* cpv_first, void* cpv_second);

/* cstl container */
/* vector_t */
extern void _type_init_vector(const void* cpv_input, void* pv_output);
extern void _type_copy_vector(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_vector(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_vector(const void* cpv_input, void* pv_output);
/* list_t */
extern void _type_init_list(const void* cpv_input, void* pv_output);
extern void _type_copy_list(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_list(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_list(const void* cpv_input, void* pv_output);
/* slist_t */
extern void _type_init_slist(const void* cpv_input, void* pv_output);
extern void _type_copy_slist(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_slist(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_slist(const void* cpv_input, void* pv_output);
/* deque_t */
extern void _type_init_deque(const void* cpv_input, void* pv_output);
extern void _type_copy_deque(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_deque(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_deque(const void* cpv_input, void* pv_output);
/* stack_t */
extern void _type_init_stack(const void* cpv_input, void* pv_output);
extern void _type_copy_stack(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_stack(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_stack(const void* cpv_input, void* pv_output);
/* queue_t */
extern void _type_init_queue(const void* cpv_input, void* pv_output);
extern void _type_copy_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_queue(const void* cpv_input, void* pv_output);
/* priority_queue_t */
extern void _type_init_priority_queue(const void* cpv_input, void* pv_output);
extern void _type_copy_priority_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_priority_queue(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_priority_queue(const void* cpv_input, void* pv_output);
/* set_t */
extern void _type_init_set(const void* cpv_input, void* pv_output);
extern void _type_copy_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_set(const void* cpv_input, void* pv_output);
/* map_t */
extern void _type_init_map(const void* cpv_input, void* pv_output);
extern void _type_copy_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_map(const void* cpv_input, void* pv_output);
/* multiset_t */
extern void _type_init_multiset(const void* cpv_input, void* pv_output);
extern void _type_copy_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_multiset(const void* cpv_input, void* pv_output);
/* multimap_t */
extern void _type_init_multimap(const void* cpv_input, void* pv_output);
extern void _type_copy_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_multimap(const void* cpv_input, void* pv_output);
/* hash_set_t */
extern void _type_init_hash_set(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_set(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_set(const void* cpv_input, void* pv_output);
/* hash_map_t */
extern void _type_init_hash_map(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_map(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_map(const void* cpv_input, void* pv_output);
/* hash_multiset_t */
extern void _type_init_hash_multiset(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_multiset(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_multiset(const void* cpv_input, void* pv_output);
/* hash_multimap_t */
extern void _type_init_hash_multimap(const void* cpv_input, void* pv_output);
extern void _type_copy_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_hash_multimap(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_hash_multimap(const void* cpv_input, void* pv_output);
/* pair_t */
extern void _type_init_pair(const void* cpv_input, void* pv_output);
extern void _type_copy_pair(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_pair(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_pair(const void* cpv_input, void* pv_output);
/* string_t */
extern void _type_init_string(const void* cpv_input, void* pv_output);
extern void _type_copy_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_string(const void* cpv_input, void* pv_output);
/* iterator_t */
extern void _type_init_iterator(const void* cpv_input, void* pv_output);
extern void _type_copy_iterator(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_iterator(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_iterator(const void* cpv_input, void* pv_output);
/* range_t */
extern void _type_init_range(const void* cpv_input, void* pv_output);
extern void _type_copy_range(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_range(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_range(const void* cpv_input, void* pv_output);
/* basic_string_t */
extern void _type_init_basic_string(const void* cpv_input, void* pv_output);
extern void _type_copy_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_basic_string(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_basic_string(const void* cpv_input, void* pv_output);

/* _Bool */
extern void _type_init_bool(const void* cpv_input, void* pv_output);
extern void _type_copy_bool(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_bool(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_bool(const void* cpv_input, void* pv_output);
/* long long */
extern void _type_init_long_long(const void* cpv_input, void* pv_output);
extern void _type_copy_long_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_long_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_long_long(const void* cpv_input, void* pv_output);
/* unsigned long long */
extern void _type_init_ulong_long(const void* cpv_input, void* pv_output);
extern void _type_copy_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_less_ulong_long(const void* cpv_first, const void* cpv_second, void* pv_output);
extern void _type_destroy_ulong_long(const void* cpv_input, void* pv_output);

#ifdef __cplusplus
}
#endif
#endif 
