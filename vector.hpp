

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP

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

	};
}


#endif
