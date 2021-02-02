

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
			struct enable_if { };

		template <typename Result>
			struct enable_if<true, Result> {
    			typedef Result type;
			};


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
		list(InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename enable_if< !std::numeric_limits<InputIt>::is_specialized >::type* = 0) :
				_head(NULL), _tail(NULL), _allocator(alloc) {

				assignment_templ(first, last);
		}
		explicit list( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
		_head(NULL), _tail(NULL), _allocator(alloc) {
			assignment(count, value);
		}
		list(const list& other) {
			*this = other;
		}
		//end of constructors


	private:

	

		//struct for element of list
		typedef struct Node
		{
			explicit Node(const T &element) : _element(element) {}
			Node() {}
			value_type _element;
			struct Node *_next;
			struct Node *_prev;

		}				node;

	public:
		//iterator
		typedef class iterator {
		private:
			node *ptr;
		public:
			iterator() : ptr(NULL) {}
			iterator(const iterator &iter) { *this = iter; }
			explicit iterator(node *ptr) : ptr(ptr) {}
			iterator &operator=(const iterator &iter) { ptr = iter.ptr; return (*this); }
			bool operator==(const iterator &iter) { return (ptr == iter.ptr); }
			bool operator!=(const iterator &iter) { return (!(*this == iter)); }
			iterator &operator++() {
				if (ptr)
					ptr = ptr->_next;
				return (*this);
			}
			iterator &operator--() {
				if (ptr)
					ptr = ptr->_prev;
				return (*this);
			}
			iterator operator++(int ) {
				iterator old_value(*this);
				if (ptr)
					ptr = ptr->_next;
				return (old_value);
			}
			iterator operator--(int ) {
				iterator old_value(*this);
				if (ptr)
					ptr = ptr->_prev;
				return (old_value);
			}
			T &operator*() { return (ptr->_element); }
		}								iterator;

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
		iterator begin() {
			return (iterator (_head));
		}
	//	const_iterator begin() const;
		iterator end() {
			if (!empty())
				return (iterator (_tail->_next));
		return (begin());
		}

		iterator insert(iterator pos, const T& value) {

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
		void push_back( const T& value ) {
			insert(end(), value);
		}
		void push_front( const T& value ) {
			insert(begin(), value);
		}
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
			ptr->_next->_prev = ptr->_prev;
			ptr->_prev->_next = ptr->_next;
			delete ptr;
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
		void pop_back() {
			erase(--end());
		}
		void pop_front() {
			erase(begin());
		}
		void resize( size_type count, T value = T() ) {
			if (count > size())
			{
				while (count-- != size())
					pop_back();
			}
			else
			{
				while (count++ != size())
					push_back(value);
			}
		}
		//destructor
		~list() {
			delete_list();
		}
	private:

		node *_head;
		node *_tail;
		allocator_type _allocator;

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
				for (node *tmp = _head; tmp != _tail->_next; tmp = tmp->_next)
					delete tmp;
				delete _tail->_next;
			}
			_head = NULL;
			_tail = NULL;
		}

		void ptr_reassignment(node **elem, node **tmp, const T &value) {
			*tmp = init_element(value);
			(*elem)->_next = *tmp;
			(*tmp)->_prev = *elem;
			*elem = *tmp;
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
		void print_list() {

			node *tmp = _head;
			if (tmp)
			{
				while (tmp != _tail->_next)
				{

					std::cout << tmp->_element << std::endl;
					tmp = tmp->_next;
				}
			}
		}
	};
}

#endif
