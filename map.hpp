

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
		friend class map;

	protected:
		Compare _c;
		value_compare( Compare c) : _c(c) {}

	public:
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
			insert(first, last);
		}
		map( const map& other ) : BinaryTree<Key, T, Compare>(), _size(0) {
			*this = other;
		}
		~map() {}
		map& operator=( const map& other ) {

			//_tree = other._tree;
			if (this == &other)
				return (*this);
			this->delete_tree(this->_root);
			this->_root = this->_NULL;
			this->_comparator = other._comparator;
			this->_root = this->copy_tree(this->_NULL, other._root, other._NULL, other._min, other._max);
			this->_NULL->_right = this->_max;
			this->_NULL->_left = this->_min;
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

		typedef class const_iterator : public iterator {
		public:
			const_iterator() : iterator() {}
			const_iterator(const const_iterator &iter) : iterator(iter) {}
			explicit const_iterator(typename base_iterator::Node *ptr, typename base_iterator::Node *N) : iterator(ptr, N) {}
			const_iterator(iterator iter) : iterator(iter) {}
			const value_type &operator*() { return (this->ptr->_pair); }
			const value_type *operator->() const { return (&(this->ptr->_pair));}
		}									const_iterator;


		typedef class reverse_iterator : public base_iterator
		{
		public:
			reverse_iterator() : base_iterator() {}
			reverse_iterator(const reverse_iterator &iter) : base_iterator(iter) {}
			reverse_iterator(typename base_iterator::Node *ptr, typename base_iterator::Node *N) : base_iterator(ptr, N) {}
			reverse_iterator &operator=(const reverse_iterator &iter) {
				if (this == &iter)
					return (*this);
				this->ptr = iter.ptr;
				this->_NULL_ = iter._NULL_;
				return (*this);
			}
			reverse_iterator &operator++() {
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
			reverse_iterator &operator--() {
				if (this->ptr->_right != this->_NULL_)
					this->ptr = this->tree_min(this->ptr->_right);
				else {
					while (this->ptr->_parent != this->_NULL_ && this->ptr->_parent->_left != this->ptr)
						this->ptr = this->ptr->_parent;
					this->ptr = this->ptr->_parent;
				}
				return (*this);
			}
			reverse_iterator operator++(int ) {
				reverse_iterator old_value(*this);
				++(*this);
				return (old_value);
			}
			reverse_iterator operator--(int ) {
				reverse_iterator old_value(*this);
				--(*this);
				return (old_value);
			}
		}								reverse_iterator;

		typedef class const_reverse_iterator : public reverse_iterator {
		public:
			const_reverse_iterator() : iterator() {}
			const_reverse_iterator(const const_reverse_iterator &iter) : reverse_iterator(iter) {}
			explicit const_reverse_iterator(typename base_iterator::Node *ptr, typename base_iterator::Node *N) : reverse_iterator(ptr, N) {}
			const_reverse_iterator(iterator iter) : reverse_iterator(iter) {}
			const value_type &operator*() { return (this->ptr->_pair); }
			const value_type *operator->() const { return (&(this->ptr->_pair));}
		}									const_reverse_iterator;

		iterator begin() { return (iterator(this->_min, this->_NULL)); }
		const_iterator begin() const { return (const_iterator(this->_min, this->_NULL)); }
		iterator end() { return (iterator(this->_NULL, this->_NULL)); }
		const_iterator end() const { return (const_iterator(this->_NULL, this->_NULL)); }

		reverse_iterator rbegin() { return (reverse_iterator(this->_max, this->_NULL)); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->_max, this->_NULL)); }
		reverse_iterator rend() { return (reverse_iterator(this->_NULL, this->_NULL)); }
		const_reverse_iterator rend() const { return (const_reverse_iterator(this->_NULL, this->_NULL)); }

		ft::pair<iterator,bool> insert( const value_type& value ) {
			ft::pair<typename BinaryTree<Key, T, Compare>::Node *, bool> pair = this->insert_key(value.first, value.second);
			if (pair.second)
				++_size;
			return (ft::make_pair(iterator(pair.first, this->_NULL), pair.second));
		}
		template< class InputIt >
		void insert( InputIt first, InputIt last ) {
			while (first != last)
			{
				if ((this->insert_key(first->first, first->second)).second)
					++_size;
				++first;
			}
		}

		iterator insert( iterator hint, const value_type& value ) {
			(void )hint;
			return (insert(value).first);
		}
		size_type count( const Key& key ) const {
			typename BinaryTree<Key, T, Compare>::Node *iter = this->_root;
			while (iter != this->_NULL)
			{
				if (!this->_comparator(key, iter->_pair.first) && !this->_comparator(iter->_pair.first, key))
					return (1);
				else if (this->_comparator(key, iter->_pair.first))
					iter = iter->_left;
				else
					iter = iter->_right;
			}
			return (0);
		}
		T& operator[]( const Key& key ) {
			return (insert(ft::make_pair(key, T())).first->second);
		}
		void erase( iterator pos ) {
			if (this->delete_node(pos->first))
				++_size;
		}
		size_type erase( const key_type& key ) {
			size_type size = this->delete_node(key);
			if (size)
				++_size;
			return (size);
		}
		void erase( iterator first, iterator last ) {
			iterator tmp;
			while (first != last)
			{
				tmp = first;
				++first;
				if (this->delete_node(tmp->first))
					++_size;
			}
		}
		iterator find( const Key& key ) {
			typename BinaryTree<Key, T, Compare>::Node *iter = this->_root;
			while (iter != this->_NULL)
			{
				if (!this->_comparator(key, iter->_pair.first) && !this->_comparator(iter->_pair.first, key))
					return (iterator(iter, this->_NULL));
				else if (this->_comparator(key, iter->_pair.first))
					iter = iter->_left;
				else
					iter = iter->_right;
			}
			return (end());
		}
		const_iterator find( const Key& key ) const {
			typename BinaryTree<Key, T, Compare>::Node *iter = this->_root;
			while (iter != this->_NULL)
			{
				if (!this->_comparator(key, iter->_pair.first) && !this->_comparator(iter->_pair.first, key))
					return (const_iterator(iter, this->_NULL));
				else if (this->_comparator(key, iter->_pair.first))
					iter = iter->_left;
				else
					iter = iter->_right;
			}
			return (end());
		}
		iterator lower_bound( const Key& key ) {
			iterator it = begin();
			while (it != end())
			{
				if (!this->_comparator(it->first, key))
					return (it);
				++it;
			}
			return (it);
		}
		const_iterator lower_bound( const Key& key ) const {
			const_iterator it = begin();
			while (it != end())
			{
				if (!this->_comparator(it->first, key))
					return (it);
				++it;
			}
			return (it);
		}
		iterator upper_bound( const Key& key ) {
			iterator it = begin();
			while (it != end())
			{
				if (this->_comparator(key, it->first))
					return (it);
				++it;
			}
			return (it);
		}
		const_iterator upper_bound( const Key& key ) const {
			const_iterator it = begin();
			while (it != end())
			{
				if (this->_comparator(key, it->first))
					return (it);
				++it;
			}
			return (it);
		}
		ft::pair<iterator,iterator> equal_range( const Key& key ) {
			iterator it = lower_bound(key);
			if (!this->_comparator(key, it->first) && !this->_comparator(it->first, key))
				return (ft::make_pair(it, ++it));
			return (ft::make_pair(it, it));
		}
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
			const_iterator it = lower_bound(key);
			if (!this->_comparator(key, it->first) && !this->_comparator(it->first, key))
				return (ft::make_pair(it, ++it));
			return (ft::make_pair(it, it));
		}
		key_compare key_comp() const {
			return (this->_comparator);
		}
		value_compare value_comp() const {
			return (value_compare(this->_comparator));
		}
	};
	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it_lhs = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator  it_rhs = rhs.begin();
		while (it_lhs != lhs.end() && it_rhs != rhs.end())
		{
			if (*it_lhs != *it_rhs)
				return (false);
			++it_rhs;
			++it_lhs;
		}
		return (!(it_lhs != lhs.end() || it_rhs != rhs.end()));
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it_lhs = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it_rhs = rhs.begin();
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
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (!(rhs < lhs));
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (rhs < lhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (!(lhs < rhs));
	}

}


#endif
