

#ifndef CONTAINERS_LIST_HPP
#define CONTAINERS_LIST_HPP

#include <iostream>


namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class list
	{

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
		list(InputIt first, InputIt last, const Allocator& alloc = Allocator()) :
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
		class iterator {
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
				ptr = ptr->_next;
				return (*this);
			}
			iterator &operator--() {
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
		};

		typedef iterator iterator;

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
		void assign( InputIt first, InputIt last ) {
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

			iterator it = begin();
			node *ptr = _head;

			while (it != pos)
			{
				ptr = ptr->_next;
				it++;
			}
			node *new_element = init_element(value);
			if (it == end())
				_tail = new_element;
			if (it == begin())
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
