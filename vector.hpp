

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

#include <iostream>

namespace ft {

	template< class T, class Allocator = std::allocator<T> >
	class vector {

 	public:

		//typedefs
		typedef size_t size_type;
		typedef typename Allocator::pointer pointer;
		typedef Allocator allocator_type;
		typedef T value_type;
		typedef int difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::const_pointer const_pointer;


	private:
		value_type *_array;
		allocator_type _allocator;

	public:

		vector() : _array(NULL) {}
		explicit vector( const Allocator& alloc ) : _array(NULL), _allocator(alloc) {}
//		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) {}
	};
}


#endif
