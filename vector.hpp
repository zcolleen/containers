

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
		size_type _capacity;
		allocator_type _allocator;

		class base_iterator {

		protected:
			T *ptr;
		public:
			base_iterator() : ptr(NULL) {}
			explicit base_iterator(T *ptr) : ptr(ptr) {}
			//g_iterator(const I &iter) { *this = iter; }
			base_iterator(const base_iterator &iter) { this->ptr = iter.ptr; }
			bool operator==(const base_iterator &iter) const { return (ptr == iter.ptr); }
			bool operator!=(const base_iterator &iter) const { return (!(*this == iter)); }
			bool operator<(const base_iterator &iter) const { return (this->ptr < iter.ptr); }
			bool operator<=(const base_iterator &iter) const { return (*this < iter || *this == iter); }
			bool operator>(const base_iterator &iter) const { return (this->ptr > iter.ptr); }
			bool operator>=(const base_iterator &iter) const { return (*this > iter || *this == iter); }
			T &operator*() const { return (*(this->ptr)); }
			T &operator[](int n) const { return (*(this->ptr + n)); }
			T *operator->() const { return (&(this->ptr));}
		};

		template <bool Cond, typename Result = void>
		struct enable_if {};

		template <typename Result>
		struct enable_if<true, Result> { typedef Result type; };

		void init_array(size_type count, const T& value)
		{
			if (count)
			{
				_array = _allocator.allocate(count);
				for (size_type i = 0; i < count; ++i)
					_allocator.construct(_array + i, value);
			}
			_size = count;
			_capacity = _size;
		}

		template<class InputIt>
		void init_array_it( InputIt first, InputIt last)
		{
			_size = 0;
			for (InputIt tmp(first); tmp != last; ++tmp)
				++_size;
			if (_size)
				_array = _allocator.allocate(_size);
			for (size_type p = 0; first != last; ++p, ++first)
				_allocator.construct(_array + p, *first);
			_capacity = _size;
		}
		void delete_vector(bool deallocate = true) {
			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(_array + i);
			if (deallocate)
			{
				_allocator.deallocate(_array, _capacity);
				_array = NULL;
			}
			_size = 0;
			//_array = NULL;
		}

		void print_vector()
		{
			std::cout << "Your vector: ";
			for (size_type i = 0; i < _size; ++i)
				std::cout << " " << _array[i];
			std::cout << std::endl;
		}

	public:

		//constructors
		vector() : _array(NULL), _size(0) {}
		explicit vector( const Allocator& alloc ) : _array(NULL), _size(0), _allocator(alloc) {}
		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _array(NULL),
		 _allocator(alloc) {
			init_array(count, value);
		}
		template< class InputIt >
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		  typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0 ) :
		  _array(NULL), _allocator(alloc) {
			init_array_it(first, last);
		}
		vector( const vector& other ) : _array(NULL), _size(0) { *this = other; }

		vector& operator=( const vector& other ) {
			if (this == &other)
				return (*this);
			delete_vector();
			_allocator = other._allocator;
			_size = other._size;
			_capacity = _size;
			if (_size)
				_array = _allocator.allocate(_size);
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_array + i, other._array[i]);
			return (*this);
		}

		//iterators
		typedef class iterator : public base_iterator
		{
		public:
			iterator(const iterator &iter) : base_iterator(iter) {}
			iterator() : base_iterator() {}
			explicit iterator(T *ptr) : base_iterator(ptr) {}
			iterator &operator=(const iterator &iter) {
				if (this != &iter)
					this->ptr = iter.ptr;
				return (*this);
			}
			iterator &operator++() { ++this->ptr; return (*this); }
			iterator &operator--() { --this->ptr; return (*this); }
			iterator operator++(int ) {
				iterator old_value(*this);
				++this->ptr;
				return (old_value);
			}
			iterator operator--(int ) {
				iterator old_value(*this);
				--this->ptr;
				return (old_value);
			}
			iterator &operator+=(int n) { this->ptr += n; return (*this); }
			iterator &operator-=(int n) { this->ptr -= n; return (*this); }
			iterator operator+(int n) { iterator tmp(*this); return (tmp += n); }
			iterator operator-(int n) { iterator tmp(*this); return (tmp -= n); }
			difference_type operator-(iterator it) { return (this->ptr - it.ptr); }

		}								iterator;

		typedef class const_iterator : public iterator {
		public:
			const_iterator() : iterator() {}
			const_iterator(const const_iterator &iter) : iterator(iter) {}
			explicit const_iterator(T *ptr) : iterator(ptr) {}
			const_iterator(iterator iter) : iterator(iter) {}
			const T &operator*() const { return (*(this->ptr)); }
		}									const_iterator;

		typedef class reverse_iterator : public base_iterator
		{
		public:
			reverse_iterator(const reverse_iterator &iter) : base_iterator(iter) {}
			reverse_iterator() : base_iterator() {}
			explicit reverse_iterator(T *ptr) : base_iterator(ptr) {}
			reverse_iterator &operator=(const reverse_iterator &iter) {
				if (this != &iter)
					this->ptr = iter.ptr;
				return (*this);
			}
			reverse_iterator &operator++() { --this->ptr; return (*this); }
			reverse_iterator &operator--() { ++this->ptr; return (*this); }
			reverse_iterator operator++(int ) {
				reverse_iterator old_value(*this);
				--this->ptr;
				return (old_value);
			}
			reverse_iterator operator--(int ) {
				reverse_iterator old_value(*this);
				++this->ptr;
				return (old_value);
			}
			reverse_iterator &operator+=(int n) { this->ptr -= n; return (*this); }
			reverse_iterator &operator-=(int n) { this->ptr += n; return (*this); }
			reverse_iterator operator+(int n) { reverse_iterator tmp(*this); return (tmp += n); }
			reverse_iterator operator-(int n) { reverse_iterator tmp(*this); return (tmp -= n); }
			difference_type operator-(reverse_iterator it) { return (it.ptr - this->ptr); }

		}								reverse_iterator;

		typedef class const_reverse_iterator : public reverse_iterator {
		public:
			const_reverse_iterator() : reverse_iterator() {}
			const_reverse_iterator(const const_reverse_iterator &iter) : reverse_iterator(iter) {}
			explicit const_reverse_iterator(T *ptr) : reverse_iterator(ptr) {}
			const_reverse_iterator(reverse_iterator iter) : reverse_iterator(iter) {}
			const T &operator*() const { return (*(this->ptr)); }
		}									const_reverse_iterator;

		void assign( size_type count, const T& value ) {
			delete_vector();
			init_array(count, value);
		}

		template< class InputIt >
		void assign( InputIt first, InputIt last,
			   typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0 ) {
			delete_vector();
			init_array_it(first, last);
		}

		iterator insert( iterator pos, const T& value )
		{
			size_type dist_before_pos = pos - begin();
			insert(pos, 1, value);
			return (iterator (_array + dist_before_pos));
		}

		void insert( iterator pos, size_type count, const T& value ) {
			ssize_t dist_before_pos = pos - begin();
			ssize_t dist_after_pos = end() - pos;
			if (count + _size <= 2 * _capacity)
			{
				if (count + _size > _capacity)
				{
					if (_capacity == 0)
						reallocation(dist_before_pos, dist_after_pos, count, value, 1 + _capacity);
					else
						reallocation(dist_before_pos, dist_after_pos, count, value, 2 * _capacity);
				}
				else {
					if (_size)
					{
						for (ssize_t i = dist_after_pos - 1; i >= 0; --i)
						{
							_allocator.construct(_array + dist_before_pos + count + i, *(_array + dist_before_pos + i));
							_allocator.destroy(_array + dist_before_pos + i);
						}
					}
					for (size_type i = dist_before_pos; i < count + dist_before_pos; ++i)
						_allocator.construct(_array + i, value);
				}
			}
			else
				reallocation(dist_before_pos, dist_after_pos, count, value, count + _size);
			_size += count;
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last,
			   typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0)
		{
			ssize_t dist_before_pos = pos - begin();
			ssize_t dist_after_pos = end() - pos;
			size_type count = distance(first, last);
			if (count + _size <= 2 * _capacity)
			{
				if (count + _size > _capacity)
				{
					if (_capacity == 0)
						reallocation_tp(dist_before_pos, dist_after_pos, count, first, last, 1 + _capacity);
					else
						reallocation_tp(dist_before_pos, dist_after_pos, count, first, last, 2 * _capacity);
				}
				else {
					if (_size)
					{
						for (ssize_t i = dist_after_pos - 1; i >= 0; --i)
						{
							_allocator.construct(_array + dist_before_pos + count + i, *(_array + dist_before_pos + i));
							_allocator.destroy(_array + dist_before_pos + i);
						}
					}
					for (size_type i = dist_before_pos; first != last; ++first, ++i)
						_allocator.construct(_array + i, *first);
				}
			}
			else
				reallocation_tp(dist_before_pos, dist_after_pos, count, first, last, count + _size);
			_size += count;
		}

		void push_back( const T& value ) {
			insert(end(), value);
		}

		iterator erase( iterator pos ) {
			return (erase(pos, ++pos));
		}
		iterator erase( iterator first, iterator last )
		{
			size_type dist_before_first = first - begin();
			size_type dist_after_last = end() - last;
			size_type range = last - first;
			for (size_type i = 0; i < dist_after_last; ++i)
			{
				*(_array + dist_before_first + i) = *(_array + dist_before_first + range + i);
				_allocator.destroy(_array + dist_before_first + range + i);
			}
			for (size_type i = dist_after_last + dist_before_first; i < _size; ++i)
				_allocator.destroy(_array + i);
			_size -= range;
			return (iterator(_array + dist_before_first));
		}
		void pop_back() {
			erase(--end(), end());
		}

		void resize( size_type count, T value = T() )
		{
			if (count > _size)
				insert(end(), count - _size, value);
			else
				erase(begin() + count, end());
		}
		reference at( size_type pos ) {

			if (pos >= _size || pos < 0)
				throw std::out_of_range("vector");
			return (_array[pos]);
		}

		const_reference at( size_type pos ) const {
			if (pos >= _size || pos < 0)
				throw std::out_of_range("vector");
			return (_array[pos]);
		}

		reference operator[]( size_type pos ) { return (_array[pos]); }
		const_reference operator[]( size_type pos ) const { return (_array[pos]); }

		size_type size() const { return (_size); }

		bool empty() const { return (_size == 0); }

		size_type capacity() const { return (_capacity); }

		reference front() { return (_array[0]); }
		const_reference front() const { return (_array[0]); }

		reference back() { return (_array[_size - 1]); }
		const_reference back() const { return (_array[_size - 1]); }

		size_type max_size() const { return (std::numeric_limits<size_type>::max() / sizeof(T)); }

		void clear() { delete_vector(false); }

		iterator begin() { return (iterator(_array)); }
		const_iterator begin() const { return (const_iterator(_array)); }
		iterator end() { return (iterator(_array + _size)); }
		const_iterator end() const { return (const_iterator(_array + _size)); }
		reverse_iterator rbegin() { return (reverse_iterator(_array + _size - 1)); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(_array + _size - 1)); }
		reverse_iterator rend() { return (reverse_iterator(_array - 1)); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(_array - 1)); }

		void reserve( size_type new_cap ) {
			if (new_cap > max_size())
				throw std::length_error("vector");
			if (new_cap > _capacity)
			{
				T *new_array;
				size_type size;
				new_array = _allocator.allocate(new_cap);
				for (size = 0; size < _size; ++size)
					_allocator.construct(new_array + size, *(_array + size));
				delete_vector();
				_size = size;
				_array = new_array;
				_capacity = new_cap;
			}
		}

		void swap( vector& other ) {
			T *array = _array;
			size_type size = _size;
			size_type capacity = _capacity;
			_array = other._array;
			_size = other._size;
			_capacity = other._capacity;
			other._array = array;
			other._size = size;
			other._capacity = capacity;
		}
		friend iterator operator+(int n, iterator &iter) { return (iter + n); }
		friend const_iterator operator+(int n, const_iterator &iter) { return (iter + n); }
		friend reverse_iterator operator+(int n, reverse_iterator &iter) { return (iter + n); }
		friend const_reverse_iterator operator+(int n, const_reverse_iterator &iter) { return (iter + n); }

		//destructor
		~vector() { delete_vector(); }

	private:

		template<typename InputIt>
		size_type distance(InputIt first, InputIt last)
		{
			size_type distance = 0;

			while (first++ != last)
				++distance;
			return (distance);
		}

		void reallocation(ssize_t dist_before_pos, ssize_t dist_after_pos, size_type count, const T& value,
					size_type allocation_value)
		{
			T *array = _array;
			_array = _allocator.allocate(allocation_value);
			copy_before_position(&array, dist_before_pos);
			for (size_type i = 0; i < count; ++i)
				_allocator.construct(_array + dist_before_pos + i, value);
			copy_after_position(&array, dist_before_pos, dist_after_pos, count);
			_allocator.deallocate(array, _capacity);
			_capacity = allocation_value;
		}

		template<typename InputIt>
		void reallocation_tp(ssize_t dist_before_pos, ssize_t dist_after_pos, size_type count, InputIt first, InputIt last,
						  size_type allocation_value)
		{
			T *array = _array;
			_array = _allocator.allocate(allocation_value);
			copy_before_position(&array, dist_before_pos);
			for (size_type i = 0; first != last; ++first, ++i)
				_allocator.construct(_array + dist_before_pos + i, *first);
			copy_after_position(&array, dist_before_pos, dist_after_pos, count);
			_allocator.deallocate(array, _capacity);
			_capacity = allocation_value;
		}
		void copy_before_position(T **array, ssize_t dist_before_pos)
		{
			for (ssize_t i = 0; i < dist_before_pos; ++i)
			{
				_allocator.construct(_array + i, *(*array + i));
				_allocator.destroy(*array + i);
			}
		}
		void copy_after_position(T **array, ssize_t dist_before_pos, ssize_t dist_after_pos, size_type count)
		{
			for (ssize_t i = dist_before_pos; i < dist_after_pos + dist_before_pos; ++i)
			{
				_allocator.construct(_array + count + i, *(*array + i));
				_allocator.destroy(*array + i);
			}
		}
	};
	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		typename ft::vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator it_rhs = rhs.begin();
		while (it_lhs != lhs.end() && it_rhs != rhs.end())
		{
			if (*it_lhs != *it_rhs)
				return (false);
			++it_rhs;
			++it_lhs;
		}
		return (!(it_lhs != lhs.end() || it_rhs != rhs.end()));
	}
	template< class T, class Alloc >
	bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return (!(lhs == rhs));
	}
	template< class T, class Alloc >
	bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		typename ft::vector<T, Alloc>::const_iterator it_lhs = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator it_rhs = rhs.begin();
		while (it_lhs != lhs.end() && it_rhs != rhs.end())
		{
			if (*it_lhs < *it_rhs)
				return (true);
			else if (*it_lhs > *it_rhs)
				return (false);
			++it_rhs;
			++it_lhs;
		}
		return (it_lhs == lhs.end() && it_rhs != rhs.end());
	}
	template< class T, class Alloc >
	bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return (lhs == rhs || lhs < rhs);
	}
	template< class T, class Alloc >
	bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return (!(lhs < rhs) && (lhs != rhs));
	}
	template< class T, class Alloc >
	bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs ) {
		return (lhs == rhs || lhs > rhs);
	}
	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}


#endif
