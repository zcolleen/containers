

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
			base_iterator(Node *ptr, Node *N) : ptr(ptr), _NULL_(N) {}
			base_iterator(const base_iterator &iter) {
				this->_NULL_ = iter._NULL_;
				this->ptr = iter.ptr;
			}
			bool operator==(const base_iterator &iter) const { return (ptr == iter.ptr); }
			bool operator!=(const base_iterator &iter) const { return (!(*this == iter)); }
			value_type &operator*() const { return (this->ptr->_pair); }
			value_type *operator->() const { return (&(this->ptr->_pair));}
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
			this->_min = other._min;
			this->_max = other._max;
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
			this->_max = this->_NULL;
			this->_min = this->_NULL;
			_size = 0;
		}
		void swap( map& other ) {

			typename BinaryTree<Key, T, Compare>::Node *tmp_root = other._root;
			typename BinaryTree<Key, T, Compare>::Node *tmp_NULL = other._NULL;
			typename BinaryTree<Key, T, Compare>::Node *tmp_min = other._min;
			typename BinaryTree<Key, T, Compare>::Node *tmp_max = other._max;
			size_type tmp_size = other._size;
			Compare tmp_compare = other._comparator;
			Allocator tmp_allocator = other._allocator;

			other._root = this->_root;
			other._NULL = this->_NULL;
			other._min = this->_min;
			other._max = this->_max;
			other._size = _size;
			other._allocator = _allocator;
			other._comparator = this->_comparator;
			this->_root = tmp_root;
			this->_NULL = tmp_NULL;
			this->_min = tmp_min;
			this->_max = tmp_max;
			_size = tmp_size;
			_allocator = tmp_allocator;
			this->_comparator = tmp_compare;
		}

		typedef class iterator : public base_iterator
		{
		public:
			iterator() : base_iterator() {}
			iterator(const iterator &iter) : base_iterator(iter) {}
			iterator(typename base_iterator::Node *ptr, typename base_iterator::Node *N) : base_iterator(ptr, N) {}
			iterator &operator=(const iterator &iter) {
				if (this == &iter)
					return (*this);
				this->ptr = iter.ptr;
				this->_NULL_ = iter._NULL_;
				return (*this);
			}
			iterator &operator++() {
				if (this->ptr->_right != this->_NULL_)
					this->ptr = this->tree_min(this->ptr->_right);
				else {
					while (this->ptr->_parent != this->_NULL_ && this->ptr->_parent->_left != this->ptr)
						this->ptr = this->ptr->_parent;
					this->ptr = this->ptr->_parent;
				}
				return (*this);
			}
			iterator &operator--() {
				if (this->ptr == this->_NULL_)
					this->ptr = this->_NULL_->_right;
				else if (this->ptr->_left != this->_NULL_)
					this->ptr = this->tree_max(this->ptr->_left);
				else {
					while (this->ptr->_parent != this->_NULL_ && this->ptr->_parent->_right != this->ptr)
						this->ptr = this->ptr->_parent;
					this->ptr = this->ptr->_parent;
				}
				return (*this);
			}
			iterator operator++(int ) {
				iterator old_value(*this);
				++(*this);
				return (old_value);
			}
			iterator operator--(int ) {
				iterator old_value(*this);
				--(*this);
				return (old_value);
			}
		}								iterator;
		iterator begin() { return (iterator(this->_min, this->_NULL)); }
		//const_iterator begin() const;
		iterator end() { return (iterator(this->_NULL, this->_NULL)); }
		//const_iterator end() const;
		ft::pair<iterator,bool> insert( const value_type& value ) {
			this->
		}
//		T& operator[]( const Key& key ) {
//			return ((this->insert(key, T())).first);
//		}
	};
}


#endif
