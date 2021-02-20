

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
	typedef ft::pair<const Key, T> value_type;
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

		size_type _size;
		allocator_type _allocator;
		class base_iterator {

		public:
			typedef typename BinaryTree<Key, T, Compare>::Node Node;
			//typedef BinaryTree<Key, T, Compare>::_NULL _NULL_iter;
			base_iterator() : ptr(NULL), _NULL_(NULL) {}
			explicit base_iterator(Node *ptr, Node *N) : ptr(ptr), _NULL_(N) {}
			base_iterator(const base_iterator &iter) { this->ptr = iter.ptr; }
			bool operator==(const base_iterator &iter) const { return (ptr == iter.ptr); }
			bool operator!=(const base_iterator &iter) const { return (!(*this == iter)); }
		protected:
			Node *ptr;
			Node *_NULL_;
			Node *tree_min(Node *start) {
				while (start->_left != _NULL_)
					start = start->_left;
				return (start);
			}
			Node *tree_max(Node *start) {
				while (start->_right != _NULL_)
					start = start->_right;
				return (start);
			}
			//T &operator*() const { return (this->ptr->_element); }
			//T *operator->() const { return (&(this->ptr->_element));}
			//friend class map<Key, T>;
		};

	public:

		map() : BinaryTree<Key, T, Compare>(), _size(0) {}
		explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : BinaryTree<Key, T, Compare>(comp), _size(0), _allocator(alloc) {}
		template< class InputIt >
		map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : BinaryTree<Key, T, Compare>(comp), _size(0),
		_allocator(alloc)
		{
//			std::pair<T, bool> pair;
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
		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof (typename BinaryTree<Key, T, Compare>::Node));
		}
		void clear() {
			this->delete_tree(this->_root);
			this->_root = this->_NULL;
			_size = 0;
		}
		void swap( map& other ) {

			typename BinaryTree<Key, T, Compare>::Node *tmp_root = other._root;
			typename BinaryTree<Key, T, Compare>::Node *tmp_NULL = other._NULL;
			size_type tmp_size = other._size;
			Compare tmp_compare = other._comparator;
			Allocator tmp_allocator = other._allocator;

			other._root = this->_root;
			other._NULL = this->_NULL;
			other._size = _size;
			other._allocator = _allocator;
			other._comparator = this->_comparator;
			this->_root = tmp_root;
			this->_NULL = tmp_NULL;
			_size = tmp_size;
			_allocator = tmp_allocator;
			this->_comparator = tmp_compare;
		}
		typedef class iterator : public base_iterator
		{
		public:
			iterator() : base_iterator() {}
			iterator(const iterator &iter) : base_iterator(iter) {}
			explicit iterator(typename base_iterator::Node *ptr, typename base_iterator::Node *N) : base_iterator(ptr, N) {}
			iterator &operator=(const iterator &iter) {
				if (this != &iter)
					this->ptr = iter.ptr;
				return (*this);
			}
			iterator &operator++() {
				if (this->ptr->_right != NULL)
					this->ptr = this->tree_min(this->ptr->_right);
				//todo
				return (*this);
			}
			iterator &operator--() {
				if (this->ptr)
					this->ptr = this->ptr->_prev;
				return (*this);
			}
			iterator operator++(int ) {
				iterator old_value(*this);
				if (this->ptr)
					this->ptr = this->ptr->_next;
				return (old_value);
			}
			iterator operator--(int ) {
				iterator old_value(*this);
				if (this->ptr)
					this->ptr = this->ptr->_prev;
				return (old_value);
			}
		}								iterator;
//		T& operator[]( const Key& key ) {
//			return ((this->insert(key, T())).first);
//		}
	};
}


#endif
