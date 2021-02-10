

#ifndef CONTAINERS_LIST_HPP
#define CONTAINERS_LIST_HPP

#include <iostream>


namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class list
	{

	private:
		template <bool Cond, typename Result = void>
			struct enable_if {};

		template <typename Result>
			struct enable_if<true, Result> { typedef Result type; };

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

		//constructors
		list() : _head(NULL), _tail(NULL) {}

		explicit list( const Allocator& alloc) : _head(NULL), _tail(NULL), _allocator(alloc) {}

		template< class InputIt >
		list(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
	   typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0) :
	   _head(NULL), _tail(NULL), _allocator(alloc)
	   { assignment_templ(first, last); }

		explicit list( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
		_head(NULL), _tail(NULL), _allocator(alloc)
		{ assignment(count, value); }

		list(const list& other) { *this = other; }
		//end of constructors

	private:

		//struct for element of list
		typedef struct Node
		{
			explicit Node(const value_type &element) : _element(element) {}
			Node() {}
			value_type _element;
			struct Node *_next;
			struct Node *_prev;

		}				node;

		node *_head;
		node *_tail;
		allocator_type _allocator;

		class base_iterator {

		protected:
			node *ptr;
		public:
			base_iterator() : ptr(NULL) {}
			explicit base_iterator(node *ptr) : ptr(ptr) {}
			//g_iterator(const I &iter) { *this = iter; }
			base_iterator(const base_iterator &iter) { this->ptr = iter.ptr; }
			bool operator==(const base_iterator &iter) const { return (ptr == iter.ptr); }
			bool operator!=(const base_iterator &iter) const { return (!(*this == iter)); }
			T &operator*() const { return (this->ptr->_element); }
			T *operator->() const { return (&(this->ptr->_element));}
//			friend class list<T>;
		};

	public:

		//reverse_iterator
		typedef class reverse_iterator : public base_iterator {
		public:
			reverse_iterator(const reverse_iterator &iter) : base_iterator(iter) {}
			reverse_iterator() : base_iterator() {}
			explicit reverse_iterator(node *ptr) : base_iterator(ptr) {}
			reverse_iterator &operator=(const reverse_iterator &iter) {
				if (this != &iter)
					this->ptr = iter.ptr;
				return (*this);
			}
			reverse_iterator &operator++() {
				if (this->ptr)
					this->ptr = this->ptr->_prev;
				return (*this);
			}
			reverse_iterator &operator--() {
				if (this->ptr)
					this->ptr = this->ptr->_next;
				return (*this);
			}
			reverse_iterator operator++(int ) {
				reverse_iterator old_value(*this);
				if (this->ptr)
					this->ptr = this->ptr->_prev;
				return (old_value);
			}
			reverse_iterator operator--(int ) {
				reverse_iterator old_value(*this);
				if (this->ptr)
					this->ptr = this->ptr->_next;
				return (old_value);
			}
		}				reverse_iterator;

		typedef class const_reverse_iterator : public reverse_iterator {
		public:
			const_reverse_iterator() : reverse_iterator() {}
			const_reverse_iterator(const const_reverse_iterator &iter) : reverse_iterator(iter) {}
			explicit const_reverse_iterator(node *ptr) : reverse_iterator(ptr) {}
			const_reverse_iterator(reverse_iterator iter) : reverse_iterator (iter) {}
			const T &operator*() const { return (this->ptr->_element); }
		}									const_reverse_iterator;

		//iterator
		typedef class iterator : public base_iterator
		{
		public:
			iterator(const iterator &iter) : base_iterator(iter) {}
			iterator() : base_iterator() {}
			explicit iterator(node *ptr) : base_iterator(ptr) {}
			iterator &operator=(const iterator &iter) {
				if (this != &iter)
					this->ptr = iter.ptr;
				return (*this);
			}
			iterator &operator++() {
				if (this->ptr)
					this->ptr = this->ptr->_next;
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

		typedef class const_iterator : public iterator {
		public:
			const_iterator() : iterator() {}
			const_iterator(const const_iterator &iter) : iterator(iter) {}
			explicit const_iterator(node *ptr) : iterator(ptr) {}
			const_iterator(iterator iter) : iterator(iter) {}
			const T &operator*() { return (this->ptr->_element); }
		}									const_iterator;

		list& operator=( const list& other ) {

			if (this == &other)
				return (*this);

			node *header_ptr = other._head;
			node *tmp = NULL;
			node *elem = NULL;

			delete_list();

			if (other._head)
			{
				init_head(other._head->_element);
				elem = _head;
				header_ptr = header_ptr->_next;
				while (header_ptr != other._tail->_next)
				{
					ptr_reassignment(&elem, &tmp, header_ptr->_element);
					header_ptr = header_ptr->_next;
				}
				init_tail(tmp);
			}
			return (*this);
		}

		void assign( size_type count, const T& value ) {
			delete_list();
			assignment(count, value);
		}

		template< class InputIt >
		void assign( InputIt first, InputIt last, typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0) {
			delete_list();
			assignment_templ(first, last);
		}

		reference front() { return (_head->_element); }
		const_reference front() const { return (_head->_element); }
		reference back() { return (_tail->_element); }
		const_reference back() const { return (_tail->_element); }
		bool empty() const { return (_head == NULL); }
		size_type size() const {
			size_type size = 0;
			if (_head)
			{
				for (node *tmp = _head; tmp != _tail->_next; tmp = tmp->_next)
					++size;
			}
			return (size);
		}
		size_type max_size() const {
			return (std::numeric_limits<size_type>::max() / sizeof(node));
		}
		void clear() { delete_list(); }
		const_iterator begin() const { return (const_iterator (_head)); }
		iterator begin() { return (iterator (_head)); }
		reverse_iterator rbegin() { return (reverse_iterator (_tail)); }
		const_reverse_iterator rbegin() const { return (const_reverse_iterator (_tail)); }
		iterator end() {
			if (!empty())
				return (iterator (_tail->_next));
			return (begin());
		}
		const_iterator end() const {
			if (!empty())
				return (const_iterator (_tail->_next));
			return (begin());
		}
		reverse_iterator rend() {
			if (!empty())
				return (reverse_iterator(_head->_prev));
			return (rbegin());
		}
		const_reverse_iterator rend() const {
			if (!empty())
				return (const_reverse_iterator (_head->_prev));
			return (rbegin());
		}
		iterator insert(iterator pos, const T& value) {

			//node *ptr1 = pos.ptr;
			node *ptr = count_iter(pos, begin(), _head);
			node *new_element = init_element(value);
			if (pos == end())
				_tail = new_element;
			if (pos == begin())
				_head = new_element;
			if (ptr == NULL)
				init_tail(ptr);
			else
			{
				new_element->_next = ptr;
				new_element->_prev = ptr->_prev;
				ptr->_prev->_next = new_element;
				ptr->_prev = new_element;
			}
			return (iterator(new_element));
		}
		void insert( iterator pos, size_type count, const T& value ) {
			while (count-- > 0)
				insert(pos, value);
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last,
			   typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0) {
			while (first != last)
			{
				insert(pos, *first);
				first++;
			}
		}
		void push_back( const T& value ) { insert(end(), value); }
		void push_front( const T& value ) { insert(begin(), value); }
		iterator erase( iterator pos ) {
			if (pos == end())
				return (end());
			if (pos == begin() && _head == _tail)
			{
				delete_list();
				return (iterator(_head));
			}
			if (pos == --end())
				_tail = _tail->_prev;
			if (pos == begin())
				_head = _head->_next;
			node *ptr = count_iter(pos, begin(), _head);
			node *tmp = ptr->_next;
			remove_element(ptr);
			return (iterator(tmp));
		}
		iterator erase( iterator first, iterator last ) {
			while (first != last)
			{
				if (first == begin() && _head == _tail)
					return (erase(first));
				first = erase(first);
			}
			return (last);
		}
		void pop_back() { erase(--end()); }
		void pop_front() { erase(begin()); }
		void resize( size_type count, T value = T() ) {
			if (count > size())
			{
				while (count != size())
					push_back(value);
			}
			else
			{
				while (count != size())
					pop_back();
			}
		}
		void swap( list& other ) {
			node *tmp_head = _head;
			node *tmp_tail = _tail;

			_head = other._head;
			other._head = tmp_head;
			_tail = other._tail;
			other._tail = tmp_tail;
		}
		void reverse() {
			if (_head ==  NULL)
				return;
			node *tmp = _head;
			node *tmp_save = tmp;

			while (tmp != _tail)
				ptr_reverse(&tmp, &tmp_save);
			for (int i = 0; i < 2; ++i)
				ptr_reverse(&tmp, &tmp_save);
			tmp = _tail;
			_tail = _head;
			_head = tmp;
		}
		void sort() { sort(comparator); }
		template < class Compare >
		void sort( Compare comp ) { qsort(_head, _tail, comp); }

		void unique() { unique(binary_predicate); }
		template< class BinaryPredicate >
		void unique( BinaryPredicate p ) {
			node *tmp;

			tmp = _head;
			while (tmp != _tail)
			{
				if (p(tmp->_element, tmp->_next->_element))
				{
					if (tmp->_next == _tail)
						_tail = tmp;
					remove_element(tmp->_next);
					continue;
				}
				tmp = tmp->_next;
			}
		}
		void remove( const T& value ) { remove_if(unaryPredicate(value)); }
		template< class UnaryPredicate >
		void remove_if( UnaryPredicate p ) {
			node *tmp;

			if (_head == NULL)
				return;
			tmp = _head;
			while (tmp != _tail->_next)
			{
				if (p(tmp->_element))
				{
					if (tmp == _head && _head == _tail)
					{
						delete_list();
						return;
					}
					if (tmp == _head)
						_head = tmp->_next;
					if (tmp == _tail)
						_tail = tmp->_prev;
					tmp = tmp->_next;
					remove_element(tmp->_prev);
					continue;
				}
				tmp = tmp->_next;
			}
		}
		void splice( const_iterator pos, list& other, const_iterator it ) {

			if (it == other.end())
				return;
			bool to_delete = false;
			bool to_init_tail = false;
			node *insert_before = count_iter(pos, begin(), _head);
			node *inserted = count_iter(it, other.begin(), other._head);

			manage_heads_and_tails(to_init_tail, to_delete, inserted, insert_before, other);
			inserted->_next->_prev = inserted->_prev;
			inserted->_prev->_next = inserted->_next;
			if (to_init_tail)
				init_tail(inserted);
			else
			{
				node *tmp = insert_before->_prev;
				insert_before->_prev->_next = inserted;
				insert_before->_prev = inserted;
				inserted->_next = insert_before;
				inserted->_prev = tmp;
			}
			if (to_delete)
				other.delete_list();
		}
		void splice( const_iterator pos, list& other ) {
			splice(pos, other, other.begin(), other.end());
		}
		void splice( const_iterator pos, list& other, const_iterator first, const_iterator last) {
			const_iterator tmp;
			while (first != last)
			{
				tmp = first;
				++first;
				splice(pos, other, tmp);
			}
		}
		void merge( list& other ) {
			merge(other, comparator);
		}
		template <class Compare>
		void merge( list& other, Compare comp ) {
			if (&other == this)
				return;
			const_iterator it, it_other;
			it_other = other.begin();
			it = begin();
			while (it_other != other.end())
			{
				while (it != end())
				{
					if (comp(*it_other, *it))
					{
						splice(it, other, it_other);
						break;
					}
					++it;
				}
				if (it == end())
					splice(it, other, it_other);
				it_other = other.begin();
			}
		}
		//destructor
		~list() { delete_list(); }
	private:

		node *init_element() {
 			node *new_node = new node;

			new_node->_next = NULL;
			new_node->_prev = NULL;
			return (new_node);

		}
		node *init_element(const T &elem) {

			node *new_node = new node(elem);

			new_node->_next = NULL;
			new_node->_prev = NULL;
			return (new_node);
		}

		node *count_iter(iterator pos, iterator it, node *ptr) {

			if (pos == end() && _tail)
				return (_tail->_next);
			if (pos == --end())
				return (_tail);
			while (it != pos)
			{
				ptr = ptr->_next;
				it++;
			}
			return (ptr);
		}
		void delete_list() {

			if (_head)
			{
				node *tmp = _head;
				while (tmp != _tail->_next)
				{
					tmp = tmp->_next;
					delete tmp->_prev;
				}
				delete _tail->_next;
			}
			_head = NULL;
			_tail = NULL;
		}

		void manage_heads_and_tails(bool &to_init_tail, bool &to_delete, node *inserted, node *insert_before,
							  list &other) {
			if (_head == NULL)
				to_init_tail = true;
			if (inserted == other._head && other._head == other._tail)
				to_delete = true;
			if (insert_before == _head)
				_head = inserted;
			if (_tail && insert_before == _tail->_next)
				_tail = inserted;
			if (other._head == inserted)
				other._head = other._head->_next;
			if (other._tail == inserted)
				other._tail = other._tail->_prev;
		}
		static bool comparator(const T &a, const T &b) { return (a < b); }
		static bool binary_predicate(const T &a, const T &b) { return (a == b); }
		struct unaryPredicate {
			T _i;
			explicit unaryPredicate(const T &i) : _i(i) {}
			bool operator()(const T &i) { return (i == _i); }
		};
		void swap(node *first, node *second) {

			node *tmp_first;
			node *tmp_second;

			if (first == _head)
				_head = second;
			if (second == _tail)
				_tail = first;
			tmp_first = first->_prev;
			tmp_second = second->_next;

			first->_prev->_next = second;
			first->_prev = second->_prev;
			second->_prev->_next = first;
			second->_prev = tmp_first;
			second->_next->_prev = first;
			second->_next = first->_next;
			first->_next->_prev = second;
			first->_next = tmp_second;
		}
		template<class Compare>
		void qsort(node *plot_head, node *plot_tail, Compare comp)
		{
			node *tmp, *new_head, *new_tail;
			bool tail_swap = false;
			bool head_swap = false;
			new_head = plot_head;
			new_tail = plot_tail;

			while (plot_head != plot_tail && plot_head != plot_tail->_next)
			{
				if (comp(plot_tail->_element, plot_head->_element))
				{
					if (!tail_swap)
						new_tail = plot_head;
					tmp = plot_tail->_prev;
					swap(plot_head, plot_tail->_prev);
					swap(plot_tail->_prev, plot_tail);
					plot_head = tmp;
					if (!head_swap)
						new_head = plot_head;
					tail_swap = true;
					continue;
				}
				plot_head = plot_head->_next;
				head_swap = true;
			}
			if (new_head && new_head != plot_tail->_prev && plot_tail != new_head->_prev)
				qsort(new_head, plot_tail->_prev, comp);
			if (tail_swap && plot_tail->_next != new_tail)
				qsort(plot_tail->_next, new_tail, comp);
		}
		void remove_element(node *ptr) {
			ptr->_next->_prev = ptr->_prev;
			ptr->_prev->_next = ptr->_next;
			delete ptr;
		}
		void ptr_reassignment(node **elem, node **tmp, const T &value) {
			*tmp = init_element(value);
			(*elem)->_next = *tmp;
			(*tmp)->_prev = *elem;
			*elem = *tmp;
		}

		void ptr_reverse(node **tmp, node **tmp_save) {
			*tmp_save = (*tmp)->_next;
			(*tmp)->_next = (*tmp)->_prev;
			(*tmp)->_prev = *tmp_save;
			*tmp = *tmp_save;
		}
		template< class InputIt >
		void assignment_templ(InputIt first, InputIt last) {

			node *tmp;
			node *elem;

			if (first != last)
			{
				init_head(*first);
				elem = _head;
				while (++first != last)
					ptr_reassignment(&elem, &tmp, *first);
				init_tail(tmp);
			}
		}
		void init_head(const T& value) {
			_head = init_element(value);
		}
		void init_tail(node *tail_elem) {
			node *ptr;

			if (tail_elem)
				_tail = tail_elem;
			else
				_tail = _head;
			ptr = init_element();
			ptr->_prev = _tail;
			_tail->_next = ptr;
			ptr->_next = _head;
			_head->_prev = ptr;
		}
		void assignment(size_type count, const T& value) {

			node *tmp = NULL;
			node *elem = NULL;

			if (count > 0)
			{
				init_head(value);
				elem = _head;
				while (--count > 0)
					ptr_reassignment(&elem, &tmp, value);
				init_tail(tmp);
			}
		}
	};
	template< class T, class Alloc >
	bool operator==( const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs ) {
		typename ft::list<T, Alloc>::const_iterator it_lhs = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator it_rhs = rhs.begin();
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
	bool operator!=( const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs ) {
		return (!(lhs == rhs));
	}
	template< class T, class Alloc >
	bool operator<( const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs ) {
		typename ft::list<T, Alloc>::const_iterator it_lhs = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator it_rhs = rhs.begin();
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
	bool operator<=( const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs ) {
		return (lhs == rhs || lhs < rhs);
	}
	template< class T, class Alloc >
	bool operator>( const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs ) {
		return (!(lhs < rhs) && (lhs != rhs));
	}
	template< class T, class Alloc >
	bool operator>=( const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs ) {
		return (lhs == rhs || lhs > rhs);
	}
	template< class T, class Alloc >
	void swap( ft::list<T,Alloc>& lhs, ft::list<T,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif
