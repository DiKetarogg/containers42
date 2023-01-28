#pragma once
#include <memory>
#include "iterator.hpp"

namespace ft {

	template<class T, class Allocator = std::allocator<T>>
	class vector {
    public:
      typedef T					value_type;
      //typedef typename _Base::pointer			pointer;
      //typedef typename Allocator_traits::const_pointer	const_pointer;
      //typedef typename Allocator_traits::reference		reference;
      //typedef typename Allocator_traits::const_reference	const_reference;
      typedef pointer_iterator<pointer, vector> iterator;
      typedef pointer_iterator<const_pointer, vector>
      const_iterator;
      typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
      typedef std::reverse_iterator<iterator>		reverse_iterator;
      typedef size_t					size_type;
      typedef ptrdiff_t					difference_type;
      typedef Allocator					allocator_type;
	};

}
