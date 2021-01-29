

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

			node *tmp;
			node *elem;

			if (first != last)
			{
				_head = init_element(*first);
				elem = _head;
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
		explicit list( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
		_head(NULL), _tail(NULL), _allocator(alloc) {

			node *tmp;
			node *elem;

			if (count > 0)
			{
				_head = init_element(value);
				elem = _head;
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

		//destructor
		~list() {

			for (node *tmp = _head; tmp != NULL; tmp = tmp->_next)
				delete tmp;
		}

	private:

		typedef struct Node
		{
			explicit Node(const T &element) : _element(element) {}
			value_type _element;
			struct Node *_next;
			struct Node *_prev;

		}				node;

		node *_head;
		node *_tail;
		allocator_type _allocator;

		node *init_element(const T &elem) {

			node *new_node = new node(elem);

			new_node->_next = NULL;
			new_node->_prev = NULL;
			return (new_node);
		}


	};
}

#endif
