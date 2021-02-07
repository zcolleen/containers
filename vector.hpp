

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
		size_type _size;
		allocator_type _allocator;

		template <bool Cond, typename Result = void>
		struct enable_if {};

		template <typename Result>
		struct enable_if<true, Result> { typedef Result type; };

		void init_array(size_type count, const T& value)
		{
			if (count)
			{
				_array = _allocator.allocate(count);
				for (size_type i = 0; i < count)
					_allocator.construct(_array, value);
			}
		}

		template<class InputIt>
		void init_array_it( InputIt first, InputIt last)
		{
			InputIt tmp(first);
			size_type p = 0;
			while (tmp != last)
			{
				++_size;
				++tmp;
			}
			if (_size)
				_array = _allocator.allocate(_size)
//			while (first != last)
//			{
//				_allocator.construct(_array + p, *first)
//				++first;
//			}
			for (; first < last; ++i, ++first)
			{

			}
		}
		void delete_vector() {
			for (size_type i = 0; i < size_type; ++i)
				_allocator.destroy(_array + i);
			allocator.deallocate(_array, _size);
		}

	public:

		//constructors
		vector() : _array(NULL), _size(0) {}
		explicit vector( const Allocator& alloc ) : _array(NULL), _size(0), _allocator(alloc) {}
		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _array(NULL),
		_size(count), _allocator(alloc) {
			init_array(count, value);
		}
		template< class InputIt >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		  typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0 ) :
		  _array(NULL), _size(0), _allocator(alloc) {
			init_array_it(first, last);
		}
		vector( const vector& other ) {

		}

		//destructor
		~vector() { delete_vector(); }
	};
}


#endif
