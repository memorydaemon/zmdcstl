/*
 * cstl_memory.c
 *
 *  Created on: 6 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_memory.h"
#include "cstl_types.h"
#include "cstl_iterator.h"
#include "cstl_vector.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4146)  // unary minus operator applied to unsigned type, result still unsigned
#endif

//TODO call container-specific impl

void* align(size_t alignment, size_t size, void** ptr, size_t* space)
{
  if (*space >= size)
  {
    char* ptrAligned = (char*) (((size_t) (*ptr) + (alignment - 1)) & -alignment);
    size_t offset = (size_t) (ptrAligned - (char*) (*ptr));
    if ((*space - size) >= offset) // Have to implement this in terms of subtraction instead of addition in order to handle possible overflow.
    {
      *ptr = ptrAligned;
      *space -= offset;
      return ptrAligned;
    }
  }
  return NULL;
}

void* align_advance(size_t alignment, size_t size, void* ptr, size_t space, void** ptrAdvanced /*=null*/,
    size_t* spaceReduced /*=null*/)
{
  if (space >= size)
  {
    char* ptrAligned = (char*) (((size_t) ptr + (alignment - 1)) & -alignment);
    size_t offset = (size_t) (ptrAligned - (char*) ptr);
    if ((space - size) >= offset) // Have to implement this in terms of subtraction instead of addition in order to handle possible overflow.
    {
      if (ptrAdvanced)
        *ptrAdvanced = (ptrAligned + size);
      if (spaceReduced)
        *spaceReduced = (space - (offset + size));
      return ptrAligned;
    }
  }
  return NULL;
}

void destruct_range(forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));

  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  if (type->_t_typedestroy != NULL)
  {
    bool ret = false;
    for (; !iterator_equal(first, last); iterator_next(first))
    {
      type->_t_typedestroy(first->_t_pos, &ret);
      assert(ret);
    }
  }
}

void destruct_n(forward_iterator_t* first, int n)
{
  assert(iterator_is_valid(first));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  if (type->_t_typedestroy)
  {
    bool ret = false;
    for (; n > 0; n--)
    {
      type->_t_typedestroy(first->_t_pos, &ret);
      iterator_next(first);
      assert(ret);
    }
  }
}

void destruct_at(input_iterator_t* destination)
{
  assert(iterator_is_valid(destination));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  if (type->_t_typedestroy)
  {
    bool ret = false;
    type->_t_typedestroy(destination->_t_pos, &ret);
    assert(ret);
  }
}

void uninitialized_default_fill_n(forward_iterator_t* destination, size_t n)
{
  assert(iterator_is_valid(destination));
  bool ret = false;
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  ufun_t dctor = type->_t_typeinit;
  if(dctor)
  {
    for (; n > 0; n--)
    {
      dctor(destination->_t_pos, &ret);
      iterator_next(destination);
    }
  }else
  {
    for (; n > 0; n--, iterator_next(destination))
      memset(destination->_t_pos, 0, type->_t_typesize);
  }
}

void uninitialized_default_fill(forward_iterator_t* first, forward_iterator_t* last)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  bool ret = false;
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  for (; !iterator_equal(first, last); iterator_next(first))
  {
    if (type->_t_typeinit)
      type->_t_typeinit(first->_t_pos, &ret);
    else
      memset(first->_t_pos, 0, type->_t_typesize);
  }
}

void uninitialized_fill_n(forward_iterator_t* destination, const void* value, int n)
{
  assert(iterator_is_valid(destination));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(destination);
  for (; n > 0; n--)
  {
    if (type->_t_typecopy)
    {
      bool ret = false;
      type->_t_typecopy(destination->_t_pos, value, &ret);
      assert(ret);
    }
    else
    {
      cstl_memcpy(destination->_t_pos, value, type->_t_typesize);
    }
    iterator_next(destination);
  }
}

void uninitialized_fill(forward_iterator_t* first, forward_iterator_t* last, const void* value)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last));
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(first);
  for (; !iterator_equal(first, last); iterator_next(first))
  {
    if (type->_t_typecopy)
    {
      bool ret = false;
      type->_t_typecopy(first->_t_pos, value, &ret);
      assert(ret);
    }
    else
    {
      cstl_memcpy(first->_t_pos, value, type->_t_typesize);
    }
  }
}

#define uninitialized_copy_from_continoues_to(iterator_next)\
if (type->_t_typecopy)\
{\
  bool ret = false;\
  for (; from != end; from += tsize)\
  {\
    type->_t_typecopy(result->_t_pos, from, &ret);\
    iterator_next;\
  }\
} else\
{\
  for (; from != end; from += tsize)\
  {\
    cstl_memcpy(result->_t_pos, from, tsize);\
    iterator_next;\
  }\
}

static inline void uninitialized_copy_from_continoues(_byte_t* from, _byte_t* end, forward_iterator_t* result)
{
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(result);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(result))
  {
  case _VECTOR_CONTAINER:
  case _DEQUE_CONTAINER:
  case _BASIC_STRING_CONTAINER:
    if (type->_t_typecopy)
    {
      // this is the case uninitialized_copy_from_continoues_to_continoues,
      // but _t_typecopy not null, so have to copy on by one
      bool ret = false;
      for (; from != end; from += tsize)
      {
        type->_t_typecopy(result->_t_pos, from, &ret);
        result->_t_pos += tsize;
      }
    }
    else
    {
      // this is the case uninitialized_copy_from_continoues_to_continoues
      // and _t_typecopy null, so use memcpy
      cstl_memcpy(result->_t_pos, from, end - from);
      result->_t_pos += end - from;
    }
    break;
  case _LIST_CONTAINER:
    uninitialized_copy_from_continoues_to(/*list_iterator_next(result)*/)
    ;
    break;
  case _SLIST_CONTAINER:
    uninitialized_copy_from_continoues_to(/*slist_iterator_next(result)*/)
    ;
    break;
  case _SET_CONTAINER:
    uninitialized_copy_from_continoues_to(/*set_iterator_next(result)*/)
    ;
    break;
  case _MULTISET_CONTAINER:
    break;
  case _MAP_CONTAINER:
    break;
  case _MULTIMAP_CONTAINER:
    break;
  case _HASH_SET_CONTAINER:
    break;
  case _HASH_MULTISET_CONTAINER:
    break;
  case _HASH_MAP_CONTAINER:
    break;
  case _HASH_MULTIMAP_CONTAINER:
    break;
  default:
    break;
  }
}

#define uninitialized_copy_from_n_vector_aux(iterator_next)\
if (type->_t_typecopy)\
{\
  bool ret = false;\
  for (; nstep > 0; nstep--)\
  {\
    type->_t_typecopy(result->_t_pos, from, &ret);\
    iterator_next;\
  }\
} else\
{\
  for (; nstep > 0; nstep--)\
  {\
    cstl_memcpy(result->_t_pos, from, tsize);\
    iterator_next;\
  }\
}

static inline void uninitialized_copy_n_from_continoues(_byte_t* from, size_t nstep, forward_iterator_t* result)
{
  // if result in [vec,deque,string], use memcpy for all element
  // else if no copyfunc, use memcpy for each element
  // else use copyfunc for each element
  type_t* type = _ITERATOR_TYPE_INFO_TYPE(result);
  size_t tsize = type->_t_typesize;
  switch (_ITERATOR_CONTAINER_TYPE(result))
  {
  case _VECTOR_CONTAINER:
  case _DEQUE_CONTAINER:
  case _BASIC_STRING_CONTAINER:
    // if result in [vec,deque,string], use memcpy for all element
    if (type->_t_typecopy)
    {
      // this is the case uninitialized_copy_from_continoues_to_continoues,
      // but _t_typecopy not null, so have to copy on by one
      bool ret = false;
      _byte_t* end = from + nstep * tsize;
      for (; from != end; from += tsize)
      {
        type->_t_typecopy(result->_t_pos, from, &ret);
        result->_t_pos += tsize;
      }
    }
    else
    {
      // this is the case uninitialized_copy_from_continoues_to_continoues
      // and _t_typecopy null, so use memcpy
      nstep *= tsize;
      cstl_memcpy(result->_t_pos, from, nstep);
      result->_t_pos += nstep;
    }
    break;
  case _LIST_CONTAINER:
    uninitialized_copy_from_n_vector_aux(/*list_iterator_next(result)*/)
    ;
    break;
  case _SLIST_CONTAINER:
    uninitialized_copy_from_n_vector_aux(/*slist_iterator_next(result)*/)
    ;
    break;
  case _SET_CONTAINER:
    uninitialized_copy_from_n_vector_aux(/*set_iterator_next(result)*/)
    ;
    break;
  case _MULTISET_CONTAINER:
    break;
  case _MAP_CONTAINER:
    break;
  case _MULTIMAP_CONTAINER:
    break;
  case _HASH_SET_CONTAINER:
    break;
  case _HASH_MULTISET_CONTAINER:
    break;
  case _HASH_MAP_CONTAINER:
    break;
  case _HASH_MULTIMAP_CONTAINER:
    break;
  default:
    break;
  }
}

void uninitialized_copy(input_iterator_t* first, input_iterator_t* last, forward_iterator_t* result)
{
  assert(iterator_is_valid(first) && iterator_is_valid(last) && iterator_is_valid(result));
  assert(iterator_same_elem_type(first, last) && iterator_same_elem_type(first, result));

  switch (_ITERATOR_CONTAINER_TYPE(first))
  {
  case _VECTOR_CONTAINER:
  case _DEQUE_CONTAINER:
  case _BASIC_STRING_CONTAINER:
    uninitialized_copy_from_continoues(first->_t_pos, last->_t_pos, result);
    break;
  case _LIST_CONTAINER:
    break;
  case _SLIST_CONTAINER:
    break;
  case _SET_CONTAINER:
    break;
  case _MULTISET_CONTAINER:
    break;
  case _MAP_CONTAINER:
    break;
  case _MULTIMAP_CONTAINER:
    break;
  case _HASH_SET_CONTAINER:
    break;
  case _HASH_MULTISET_CONTAINER:
    break;
  case _HASH_MAP_CONTAINER:
    break;
  case _HASH_MULTIMAP_CONTAINER:
    break;
  default:
    break;
  }
}

void uninitialized_copy_n(input_iterator_t* first, int n_step, forward_iterator_t* result)
{
  assert(iterator_is_valid(first) && iterator_is_valid(result));

  switch (_ITERATOR_CONTAINER_TYPE(first))
  {
  case _VECTOR_CONTAINER:
  case _DEQUE_CONTAINER:
  case _BASIC_STRING_CONTAINER:
    uninitialized_copy_n_from_continoues(first->_t_pos, n_step, result);
    break;
  case _LIST_CONTAINER:
    break;
  case _SLIST_CONTAINER:
    break;
  case _SET_CONTAINER:
    break;
  case _MULTISET_CONTAINER:
    break;
  case _MAP_CONTAINER:
    break;
  case _MULTIMAP_CONTAINER:
    break;
  case _HASH_SET_CONTAINER:
    break;
  case _HASH_MULTISET_CONTAINER:
    break;
  case _HASH_MAP_CONTAINER:
    break;
  case _HASH_MULTIMAP_CONTAINER:
    break;
  default:
    break;
  }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
