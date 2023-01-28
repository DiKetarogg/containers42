#pragma once

#include <cstddef>
#include "type_traits.hpp"

namespace ft {

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template
	< class Category
	, class T
	, class Distance = std::ptrdiff_t
	, class Pointer = T*
	, class Reference = T&
	>
struct iterator {
	typedef Category  iterator_category;
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
};

template<class Iterator>
struct iterator_traits;

template<class Iterator>
struct iterator_traits {
	typedef class Iterator::iterator_category iterator_category;
	typedef class Iterator::value_type        value_type;
	typedef class Iterator::difference_type   difference_type;
	typedef class Iterator::pointer           pointer;
	typedef class Iterator::reference         reference;
};

/// Partial specialization for pointer types.
template<class T>
struct iterator_traits<T*> {
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef std::ptrdiff_t             difference_type;
	typedef T*                         pointer;
	typedef T&                         reference;
};

/// Partial specialization for const pointer types.
template<class T>
struct iterator_traits<const T*> {
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef std::ptrdiff_t             difference_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
};

template<class It, class Traits = iterator_traits<It>,
	class Category = class Traits::iterator_category>
struct is_random_access_iter
	: is_base_of<random_access_iterator_tag, Category>::value {};

template<class It>
typename It::difference_type distance(It i1, It i2);

namespace detail {

	template<class Category>
	struct distance_struct_impl {
		template<class Iterator>
		static typename iterator_traits<Iterator>
		::difference_type distance(Iterator first, Iterator last) {
			typename iterator_traits<Iterator>
				::difference_type count = 0;
			for (;first != last; ++first)
				++count;
			return count;
		}
	};

	template<>
	struct distance_struct_impl<random_access_iterator_tag> {
		template<class Iterator>
		static typename iterator_traits<Iterator>
		::difference_type distance(Iterator first, Iterator last) {
			return last - first;
		}
	};
	template<class Iterator>
	struct distance_struct
	: distance_struct_impl
		< typename iterator_traits
			<Iterator>::iterator_category
		>{};
}//detail

template<class Iterator>
typename iterator_traits<Iterator>
::difference_type distance(Iterator first, Iterator last) {
	return detail::distance_struct<Iterator>
		::distance(first, last);
}

} // namespace

namespace ft {
	template<class Type, class Container>
	class pointer_iterator;

	template<class Type, class Container>
	class pointer_iterator<Type*, Container>
		: iterator
			< typename iterator_traits<Type*>::iterator_category
			, typename iterator_traits<Type*>::value_type
			, typename iterator_traits<Type*>::difference_type
			, typename iterator_traits<Type*>::pointer
			, typename iterator_traits<Type*>::reference
			>
	{
		protected:
		typedef iterator_traits<Type*> traits;

	};
}
