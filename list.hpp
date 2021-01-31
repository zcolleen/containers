

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
			value_type _element;
			struct Node *_next;
			struct Node *_prev;

		}				node;

	public:
		//iterator
		class iterator {
		private:
			explicit iterator(node *ptr) : ptr(ptr) {}
			node *ptr;
		public:
			iterator() : ptr(NULL) {}
			iterator(const iterator &iter) { *this = iter; }
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
				this++;
				return (old_value);
			}
			iterator operator--(int ) {
				iterator old_value(*this);
				this--;
				return (old_value);
			}
			T &operator*() { return (ptr->_element); }
		};

		list& operator=( const list& other ) {

			if (this == &other)
				return (*this);

			node *header_ptr = other._head;
			node *first_ptr;
			node *second_ptr;

			for (node *tmp = _head; tmp != NULL; tmp = tmp->_next)
				delete tmp;

			if (header_ptr != NULL)
			{
				_head = init_element(header_ptr->_element);
				header_ptr = header_ptr->_next;
			}
			second_ptr = _head;
			while (header_ptr != NULL)
			{
				first_ptr = init_element(header_ptr->_element);
				second_ptr->_next = first_ptr;
				first_ptr->_prev = second_ptr;
				second_ptr = first_ptr;
				header_ptr = header_ptr->_next;
			}
			_tail = first_ptr;
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
			print_list();
		}

		reference front() { return (_head->_element); }
		const_reference front() const { return (_head->_element); }
		reference back() { return (_tail->_element); }
		const_reference back() const { return (_tail->_element); }
		bool empty() const { return (_head == NULL); }
		size_type size() const {
			size_type size = 0;
			for (node *tmp = _head; tmp != NULL; tmp = tmp->_next)
				++size;
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
				return (_tail->_next);
		return (begin());
		}

		//destructor
		~list() {
			delete_list();
		}

	private:

		node *_head;
		node *_tail;
		allocator_type _allocator;

		node *init_element(const T &elem) {

			node *new_node = new node(elem);

			new_node->_next = NULL;
			new_node->_prev = NULL;
			return (new_node);
		}

		void delete_list() {

			for (node *tmp = _head; tmp != NULL; tmp = tmp->_next)
				delete tmp;
			_head = NULL;
			_tail = NULL;
		}

		template< class InputIt >
		void assignment_templ(InputIt first, InputIt last) {

			node *tmp;
			node *elem;

			if (first != last)
			{
				_head = init_element(*first);
				elem = _head;
				_tail = _head;
				while (++first != last)
				{
					tmp = init_element(*first);
					elem->_next = tmp;
					tmp->_prev = elem;
					elem = tmp;
				}
				_tail = tmp;
			}
		}
		void assignment(size_type count, const T& value) {

			node *tmp;
			node *elem;

			if (count > 0)
			{
				_head = init_element(value);
				elem = _head;
				_tail = _head;
				while (--count > 0)
				{
					tmp = init_element(value);
					elem->_next = tmp;
					tmp->_prev = elem;
					elem = tmp;
				}
				_tail = tmp;
			}
		}
		void print_list() {

			node *tmp = _head;
			while (tmp != NULL) {

				std::cout << tmp->_element << std::endl;
				tmp = tmp->_next;
			}
		}


	};
}

#endif
