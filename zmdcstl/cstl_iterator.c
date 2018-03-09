/*
 * cstl_iterator.c
 *
 *  Created on: 7 Mar. 2018
 *      Author: jackiez
 */

#include "cstl_iterator.h"
#include "cstl_vector.h"

bool iterator_is_valid(iterator_t* it_iter)
{
    return ((it_iter->hdr->_t_containertype >= _VECTOR_CONTAINER && it_iter->hdr->_t_containertype <= _BASIC_STRING_CONTAINER)
        && (it_iter->hdr->_t_iteratortype >= _INPUT_ITERATOR && it_iter->hdr->_t_iteratortype <= _RANDOM_ACCESS_ITERATOR));
}

bool iterator_same_type(iterator_t* it_first, iterator_t* it_second)
{
    return (iterator_is_valid(it_first) &&
        iterator_is_valid(it_second) &&
        (it_first->hdr->_t_containertype == it_second->hdr->_t_containertype) &&
        (it_first->hdr->_t_iteratortype == it_second->hdr->_t_iteratortype));
}

bool iterator_before(iterator_t* it_first, iterator_t* it_second)
{
    assert(iterator_same_type(it_first, it_second));
    switch (it_first->hdr->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        //return vector_iterator_before(it_first, it_second);
        return false;
        break;
        /* case _DEQUE_CONTAINER:
             return _deque_iterator_before(it_first, it_second);
             break;
         case _LIST_CONTAINER:
             return _list_iterator_before(it_first, it_second);
             break;
         case _SLIST_CONTAINER:
             return _slist_iterator_before(it_first, it_second);
             break;
         case _SET_CONTAINER:
             return _set_iterator_before(it_first, it_second);
             break;
         case _MULTISET_CONTAINER:
             return _multiset_iterator_before(it_first, it_second);
             break;
         case _MAP_CONTAINER:
             return _map_iterator_before(it_first, it_second);
             break;
         case _MULTIMAP_CONTAINER:
             return _multimap_iterator_before(it_first, it_second);
             break;
         case _HASH_SET_CONTAINER:
             return _hash_set_iterator_before(it_first, it_second);
             break;
         case _HASH_MULTISET_CONTAINER:
             return _hash_multiset_iterator_before(it_first, it_second);
             break;
         case _HASH_MAP_CONTAINER:
             return _hash_map_iterator_before(it_first, it_second);
             break;
         case _HASH_MULTIMAP_CONTAINER:
             return _hash_multimap_iterator_before(it_first, it_second);
             break;
         case _BASIC_STRING_CONTAINER:
             return _basic_string_iterator_before(it_first, it_second);
             break;*/
    default:
        return false;
        break;
    }
}

bool iterator_limit_type(iterator_t* it_iter, iteratortype_t t_limittype)
{
    assert(iterator_is_valid(it_iter));
    switch (t_limittype)
    {
    case _INPUT_ITERATOR:
        return (it_iter->hdr->_t_iteratortype >= _INPUT_ITERATOR);
    case _OUTPUT_ITERATOR:
        return (it_iter->hdr->_t_iteratortype >= _OUTPUT_ITERATOR);
    case _FORWARD_ITERATOR:
        return (it_iter->hdr->_t_iteratortype >= _FORWARD_ITERATOR);
    case _BIDIRECTIONAL_ITERATOR:
        return (it_iter->hdr->_t_iteratortype >= _BIDIRECTIONAL_ITERATOR);
    case _RANDOM_ACCESS_ITERATOR:
        return (it_iter->hdr->_t_iteratortype >= _RANDOM_ACCESS_ITERATOR);
    default:
        assert(false);
    }
    return false;
}

const void* iterator_get_pointer_ignore_cstr(iterator_t* it_iter)
{
    assert(iterator_is_valid(it_iter));
    assert(iterator_limit_type(it_iter, _INPUT_ITERATOR));

    switch (it_iter->hdr->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        //assert(vector_iterator_valid(_VECTOR_ITERATOR_CONTAINER(it_iter), it_iter));
        //assert(!_vector_iterator_equal(it_iter, vector_end(_VECTOR_ITERATOR_CONTAINER(it_iter))));
        //return vector_iterator_get_pointer_ignore_cstr(it_iter);
        return true;
        break;
        //  case _LIST_CONTAINER:
        //    return list_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _DEQUE_CONTAINER:
        //    return deque_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _SLIST_CONTAINER:
        //    return slist_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _SET_CONTAINER:
        //    return set_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _MULTISET_CONTAINER:
        //    return multiset_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _MAP_CONTAINER:
        //    return map_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _MULTIMAP_CONTAINER:
        //    return multimap_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _HASH_SET_CONTAINER:
        //    return hash_set_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _HASH_MULTISET_CONTAINER:
        //    return hash_multiset_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _HASH_MAP_CONTAINER:
        //    return hash_map_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _HASH_MULTIMAP_CONTAINER:
        //    return hash_multimap_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
        //  case _BASIC_STRING_CONTAINER:
        //    return basic_string_iterator_get_pointer_ignore_cstr(it_iter);
        //    break;
    default:
        assert(false);
        return NULL;
        break;
    }
}

bool iterator_same_elem_type(iterator_t* it_first, iterator_t* it_second)
{
    assert(iterator_is_valid(it_first));
    assert(iterator_is_valid(it_second));
    assert(iterator_limit_type(it_first, _INPUT_ITERATOR));
    assert(iterator_limit_type(it_second, _INPUT_ITERATOR));
    assert(iterator_get_typeinfo(it_first));
    assert(iterator_get_typeinfo(it_second));
    return type_info_is_same(iterator_get_typeinfo(it_first), iterator_get_typeinfo(it_second));
}

bool iterator_equal(iterator_t* it_first, iterator_t* it_second)
{
    assert(iterator_is_valid(it_first));
    assert(iterator_is_valid(it_second));
    assert(iterator_limit_type(it_first, _INPUT_ITERATOR));
    assert(iterator_limit_type(it_second, _INPUT_ITERATOR));
    assert(iterator_get_typeinfo(it_first));
    assert(iterator_get_typeinfo(it_second));

    if (it_first->hdr->_t_containertype != it_second->hdr->_t_containertype)
        return false;

    switch (it_first->hdr->_t_containertype)
    {
        //case _VECTOR_CONTAINER:
        //    return _vector_iterator_equal(it_first, it_second);
        //    break;
        //case _LIST_CONTAINER:
        //    return _list_iterator_equal(it_first, it_second);
        //    break;
        //case _DEQUE_CONTAINER:
        //    return _deque_iterator_equal(it_first, it_second);
        //    break;
        //case _SLIST_CONTAINER:
        //    return _slist_iterator_equal(it_first, it_second);
        //    break;
        //case _SET_CONTAINER:
        //    return _set_iterator_equal(it_first, it_second);
        //    break;
        //case _MULTISET_CONTAINER:
        //    return _multiset_iterator_equal(it_first, it_second);
        //    break;
        //case _MAP_CONTAINER:
        //    return _map_iterator_equal(it_first, it_second);
        //    break;
        //case _MULTIMAP_CONTAINER:
        //    return _multimap_iterator_equal(it_first, it_second);
        //    break;
        //case _HASH_SET_CONTAINER:
        //    return _hash_set_iterator_equal(it_first, it_second);
        //    break;
        //case _HASH_MULTISET_CONTAINER:
        //    return _hash_multiset_iterator_equal(it_first, it_second);
        //    break;
        //case _HASH_MAP_CONTAINER:
        //    return _hash_map_iterator_equal(it_first, it_second);
        //    break;
        //case _HASH_MULTIMAP_CONTAINER:
        //    return _hash_multimap_iterator_equal(it_first, it_second);
        //    break;
        //case _BASIC_STRING_CONTAINER:
        //    return _basic_string_iterator_equal(it_first, it_second);
        //    break;
    default:
        assert(false);
        return false;
        break;
    }
    return false;
}

bool iterator_valid_range(iterator_t* it_first, iterator_t* it_end, iteratortype_t t_type)
{
    return (iterator_same_type(it_first, it_end) &&
        iterator_limit_type(it_first, t_type) &&
        (iterator_equal(it_first, it_end) || iterator_before(it_first, it_end)));
}

void iterator_next(iterator_t* it_iter)
{
    assert(iterator_is_valid(it_iter));
    switch (it_iter->hdr->_t_containertype)
    {
    case _VECTOR_CONTAINER:
        vector_iterator_next(it_iter);
        break;
    case _LIST_CONTAINER:
        //_list_iterator_next(it_iter);
        break;
    case _DEQUE_CONTAINER:
        //_deque_iterator_next(it_iter);
        break;
    case _SLIST_CONTAINER:
        //_slist_iterator_next(it_iter);
        break;
    case _SET_CONTAINER:
        //_set_iterator_next(it_iter);
        break;
    case _MULTISET_CONTAINER:
        //_multiset_iterator_next(it_iter);
        break;
    case _MAP_CONTAINER:
        //_map_iterator_next(it_iter);
        break;
    case _MULTIMAP_CONTAINER:
        //_multimap_iterator_next(it_iter);
        break;
    case _HASH_SET_CONTAINER:
        //_hash_set_iterator_next(it_iter);
        break;
    case _HASH_MULTISET_CONTAINER:
        //_hash_multiset_iterator_next(it_iter);
        break;
    case _HASH_MAP_CONTAINER:
        //_hash_map_iterator_next(it_iter);
        break;
    case _HASH_MULTIMAP_CONTAINER:
        //_hash_multimap_iterator_next(it_iter);
        break;
    case _BASIC_STRING_CONTAINER:
        //_basic_string_iterator_next(it_iter);
        break;
    default:
        assert(false);
        break;
    }
}
