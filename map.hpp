

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP

#include "binary_tree.hpp"


namespace ft {


	template< class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T> > >
	class map : public BinaryTree<Key, T, Compare> {

	public:

	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef int defference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;

	class value_compare {
	public:

		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

	protected:
		Compare _c;
		value_compare( Compare c) : _c(c) {}

		bool operator()( const value_type& lhs, const value_type& rhs ) const
		{
			return (_c(lhs.first, rhs.first));
		}

	};

	private:

		//BinaryTree<Key, T, Compare> _tree;
		size_type _size;
		allocator_type _allocator;

	public:

		map() : BinaryTree<Key, T, Compare>(), _size(0) {}
		explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : BinaryTree<Key, T, Compare>(comp), _size(0), _allocator(alloc) {}
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : BinaryTree<Key, T, Compare>(comp), _size(0),
		_allocator(alloc)
		{
			while (first != last)
			{
				if (this->insert(first->first, first->second))
					++_size;
				++first;
			}
		}
		map( const map& other ) {
			*this = other;
		}
		~map() {}
		map& operator=( const map& other ) {

			//_tree = other._tree;
			this->delete_tree(this->_root);
			this->_root = this->_NULL;
			this->_comparator = other._comparator;
			this->_root = this->copy_tree(this->_NULL, other._root, other._NULL);
			_allocator = other._allocator;
			_size = other._size;
			return (*this);
		}

		bool empty() const { return (_size == 0); }
		size_type size() const { return (_size); }

//		void show() { this->show(); }
//		T& operator[]( const Key& key ) {
//
//		}
	};

}


#endif