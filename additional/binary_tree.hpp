

#ifndef CONTAINERS_BINARY_TREE_HPP
#define CONTAINERS_BINARY_TREE_HPP
#define BLACK_L false
#define RED_L true
#define RED "\033[1;31m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"

#include <iostream>
#include "pair.hpp"

template< class Key, class T, class Compare = std::less<Key> >
class BinaryTree {

protected:

	typedef struct Node {


		Node() : _parent(NULL), _right(NULL), _left(NULL), _color(BLACK_L) {}

		Node(const Node *other, struct Node *node) : _pair(other->_pair.first, other->_pair.second), _parent(node), _right(node),
				_left(node), _color(other->_color) {}
		Node(const Key &key, const T &value, struct Node *node) : _pair(key, value), _parent(node), _right(node),
		_left(node), _color(RED_L) {}
		ft::pair<const Key, T> _pair;
		struct Node *_parent;
		struct Node *_right;
		struct Node *_left;
		bool 		_color;
	}				Node;

	Node *_NULL;
	Node *_root;
	Node *_min;
	Node *_max;
	Compare _comparator;
	bool _is_key_repeated;


	explicit BinaryTree(bool repeat = false) : _NULL(new Node), _root(_NULL), _min(_NULL),
	_max(_NULL), _is_key_repeated(repeat) {}
	explicit BinaryTree(const Compare &comp, bool repeat = false) : _NULL(new Node), _root(_NULL),  _min(_NULL),
	_max(_NULL), _comparator(comp), _is_key_repeated(repeat) {}
	~BinaryTree() {
		delete_tree(_root);
		delete _NULL;
	}

	Node *copy_tree(Node *parent, Node *node, Node *other_NULL, Node *other_min, Node *other_max)
	{
		if (node == other_NULL)
			return (_NULL);
		Node *newnode = new Node(node, _NULL);
		if (node == other_min)
			_min = newnode;
		if (node == other_max)
			_max = newnode;
		newnode->_parent = parent;
		newnode->_left = copy_tree(newnode, node->_left, other_NULL, other_min, other_max);
		newnode->_right = copy_tree(newnode, node->_right, other_NULL, other_min, other_max);
		return (newnode);
	}

	ft::pair<Node*, bool> insert_key(const Key &key, const T &value)
	{
		if (_root == _NULL)
		{
			_root = new Node(key, value, _NULL);
			_root->_color = BLACK_L;
			_min = _root;
			_max = _root;
			_NULL->_left = _root;
			_NULL->_right = _root;
		}
		else
			return (insert(key, value, _root));
		return (ft::make_pair(_root, true));
	}

	void rotateRight(Node *leaf)
	{
		//априорно существует ребенок
		Node *child = leaf->_left;

		leaf->_left = child->_right;
		if (child->_right != _NULL)
			child->_right->_parent = leaf;
		child->_parent = leaf->_parent;

		if (leaf->_parent != _NULL)
		{
			if (leaf == leaf->_parent->_right)
				leaf->_parent->_right = child;
			else
				leaf->_parent->_left = child;
		}
		else
		{
			_root = child;
			_root->_parent = _NULL;
		}

		child->_right = leaf;
		leaf->_parent = child;
	}

	void rotateLeft(Node *leaf)
	{
		//априорно существует ребенок
		Node *child = leaf->_right;

		leaf->_right = child->_left;
		if (child->_left != _NULL)
			child->_left->_parent = leaf;
		child->_parent = leaf->_parent;

		if (leaf->_parent != _NULL)
		{
			if (leaf == leaf->_parent->_left)
				leaf->_parent->_left = child;
			else
				leaf->_parent->_right = child;
		}
		else
		{
			_root = child;
			_root->_parent = _NULL;
		}

		child->_left = leaf;
		leaf->_parent = child;
	}

	void insertFixup(Node *leaf)
	{
		Node *uncle;
		while (leaf != _root && leaf->_parent->_color == RED_L)
		{
			if (leaf->_parent == leaf->_parent->_parent->_left)
			{
				uncle = leaf->_parent->_parent->_right;
				if (uncle != _NULL && uncle->_color == RED_L)
				{
					//если дядя красный, тогда мы просто перекрашиваем дерево и проверяем  условие для деда
					uncle->_color = BLACK_L;
					uncle->_parent->_color = RED_L;
					uncle->_parent->_left->_color = BLACK_L;
					leaf = leaf->_parent->_parent;
				} else
				{
					//если дядя черный, делаем большой поворот вправо
					if (leaf == leaf->_parent->_right)
					{
						//если дед и отец в разных направлениях, совершаем малый поворот влево
						leaf = leaf->_parent;
						rotateLeft(leaf);
					}
					//перекраска
					leaf->_parent->_color = BLACK_L;
					leaf->_parent->_parent->_color = RED_L;
					rotateRight(leaf->_parent->_parent);
				}
			} else
			{
				uncle = leaf->_parent->_parent->_left;
				if (uncle != _NULL && uncle->_color == RED_L)
				{
					//если дядя красный, тогда мы просто перекрашиваем дерево и проверяем  условие для деда
					uncle->_color = BLACK_L;
					uncle->_parent->_color = RED_L;
					uncle->_parent->_right->_color = BLACK_L;
					leaf = leaf->_parent->_parent;
				} else
				{
					//если дядя черный, делаем большой поворот влево
					if (leaf == leaf->_parent->_left)
					{
						//если дед и отец в разных направлениях, совершаем малый поворот вправо
						leaf = leaf->_parent;
						rotateRight(leaf);
					}
					//перекраска
					leaf->_parent->_color = BLACK_L;
					leaf->_parent->_parent->_color = RED_L;
					rotateLeft(leaf->_parent->_parent);
				}
			}
			_root->_color = BLACK_L;
		}
	}

	ft::pair<Node*, bool> insert(const Key &key, const T &value, Node *leaf)
	{
		Node *return_val = _NULL;
		while (leaf != _NULL)
		{
			if (!_is_key_repeated && !_comparator(key, leaf->_pair.first) && !_comparator(leaf->_pair.first, key))
			{
				//leaf->_pair.second = value;
				return (ft::make_pair(leaf, false));
			}
			else if (_comparator(key, leaf->_pair.first))
			{
				if (leaf->_left != _NULL)
					leaf = leaf->_left;
				else
				{
					leaf->_left = new Node(key, value, _NULL);
					leaf->_left->_parent = leaf;
					return_val = leaf->_left;
					if (leaf == _min) // for iterators
					{
						_min = leaf->_left;
						_NULL->_left = _min;
					}
					insertFixup(leaf->_left);
					break;
				}
			}
			else
			{
				if (leaf->_right != _NULL)
					leaf = leaf->_right;
				else
				{
					leaf->_right = new Node(key, value, _NULL);
					leaf->_right->_parent = leaf;
					return_val = leaf->_right;
					if (leaf == _max) //for iterators
					{
						_max = leaf->_right;
						_NULL->_right = _max;
					}
					insertFixup(leaf->_right);
					break;
				}
			}
		}
		return (ft::make_pair(return_val, true));
	}

	size_t delete_node(const Key &key)
	{
		return (delete_node(key, _root));
	}

	Node *tree_min_delete(Node *start) {
		if (start->_right != _NULL)
		{
			start = start->_right;
			while (start->_left != _NULL)
				start = start->_left;
		}
		else {
			while (start->_parent->_left != start)
				start = start->_parent;
			start = start->_parent;
		}
		return (start);
	}
	Node *tree_max_delete(Node *start) {

		if (start->_left != _NULL)
		{
			start = start->_left;
			while (start->_right != _NULL)
				start = start->_right;
		}
		else {
			while (start->_parent->_right != start)
				start = start->_parent;
			start = start->_parent;
		}
		return (start);
	}

	size_t delete_node_ptr(Node *leaf)
	{
		if (_min == leaf)
		{
			_min = tree_min_delete(_min);
			_NULL->_left = _min;
		}
		if (_max == leaf)
		{
			_max = tree_max_delete(_max);
			_NULL->_right = _max;
		}
		delete_node(leaf);
		return (1);
	}

	size_t delete_node(const Key &key, Node *leaf)
	{
		while (leaf != _NULL)
		{
			if (!_comparator(key, leaf->_pair.first) && !_comparator(leaf->_pair.first, key))
			{
				return (delete_node_ptr(leaf));
			}
			else if (_comparator(key, leaf->_pair.first))
				leaf = leaf->_left;
			else
				leaf = leaf->_right;
		}
		return (0);
	}

	void delete_node(Node *leaf)
	{
		if (leaf->_left == _NULL && leaf->_right == _NULL)
		{
			if (leaf->_color == RED_L)
				case_red_leaf_zero_childs(leaf);
			else
				case_black_leaf_zero_childs(leaf);
		}
		else if ((leaf->_left == _NULL && leaf->_right != _NULL ) || (leaf->_right == _NULL && leaf->_left != _NULL))
			case_black_leaf_one_child(leaf);
		else
			case_red_or_black_leaf_two_childs(leaf);
	}

	void case_red_or_black_leaf_two_childs(Node *leaf)
	{
		Node *max_left_element = leaf->_left;

		while (max_left_element->_right != _NULL)
			max_left_element = max_left_element->_right;

		if (_min == max_left_element)
			_min = leaf;
		ft::pair<const Key, T> tmp = max_left_element->_pair;
		Key *non_cast_max_elem = const_cast<Key*>(&max_left_element->_pair.first);
		*non_cast_max_elem = leaf->_pair.first;
		max_left_element->_pair.second = leaf->_pair.second;
		Key *non_cast_leaf_pair = const_cast<Key*>(&leaf->_pair.first);
		*non_cast_leaf_pair = tmp.first;
		leaf->_pair.second = tmp.second;
		if (max_left_element->_color == RED_L)
		{
			if (max_left_element->_right == _NULL && max_left_element->_left == _NULL)
				case_red_leaf_zero_childs(max_left_element);
			else//red
				case_black_leaf_one_child(max_left_element);
		}
		else
		{
			if (max_left_element->_right == _NULL && max_left_element->_left == _NULL)
				case_black_leaf_zero_childs(max_left_element);
			else
				case_black_leaf_one_child(max_left_element);
		}
	}

	void case_black_leaf_one_child(Node *leaf)
	{
		if (leaf->_right != _NULL)
		{
			if (leaf != _root)
				leaf->_right->_parent = leaf->_parent;
			else
			{
				_root = leaf->_right;
				_root->_parent = _NULL;
			}
			if (leaf->_parent != _NULL && leaf->_parent->_right == leaf)
				leaf->_parent->_right = leaf->_right;
			else if (leaf->_parent != _NULL)
				leaf->_parent->_left = leaf->_right;
//			else
//				leaf->_parent = _NULL;
			leaf->_right->_color = BLACK_L;
		}
		else
		{
			if (leaf != _root)
				leaf->_left->_parent = leaf->_parent;
			else
			{
				_root = leaf->_left;
				_root->_parent = _NULL;
			}
			if (leaf->_parent != _NULL && leaf->_parent->_left == leaf)
				leaf->_parent->_left = leaf->_left;
			else if (leaf->_parent != _NULL)
				leaf->_parent->_right = leaf->_left;
//			else
//				leaf->_parent = _NULL;
			leaf->_left->_color = BLACK_L;
		}
		delete leaf;
	}

	void case_red_leaf_zero_childs(Node *leaf)
	{
		if (leaf->_parent->_right == leaf)
			leaf->_parent->_right = _NULL;
		else
			leaf->_parent->_left = _NULL;
		delete leaf;
	}

	void fixup_case_parent_red_child_black_grandchild_black(Node *leaf, std::string part)
	{
		if (part == "LEFT")
				leaf->_left->_color = RED_L;
		else
			leaf->_right->_color = RED_L;
		leaf->_color = BLACK_L;

	}

	void fixup_case_parent_red_child_black_grandchild_red(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			if (leaf->_left->_right != _NULL && leaf->_left->_right->_color == RED_L)
				rotateLeft(leaf->_left);
			rotateRight(leaf);
			leaf->_parent->_color = RED_L;
			leaf->_color = BLACK_L;
			leaf->_parent->_left->_color = BLACK_L;
		}
		else
		{
			if (leaf->_right->_left != _NULL && leaf->_right->_left->_color == RED_L)
				rotateRight(leaf->_right);
			rotateLeft(leaf);
			leaf->_parent->_color = RED_L;
			leaf->_color = BLACK_L;
			leaf->_parent->_right->_color = BLACK_L;
		}
	}

	void fixup_case_parent_black_child_black_grandchild_red(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			if (leaf->_left->_right != _NULL)
				rotateLeft(leaf->_left);
			rotateRight(leaf);
			leaf->_parent->_color = BLACK_L;
			leaf->_parent->_left->_color = BLACK_L;
		}
		else
		{
			if (leaf->_right->_left != _NULL)
				rotateRight(leaf->_right);
			rotateLeft(leaf);
			leaf->_parent->_color = BLACK_L;
			leaf->_parent->_right->_color = BLACK_L;
		}
	}

	void fixup_case_parent_black_child_red_grandchild_black_grandgranchild_red(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			if (leaf->_left->_right != _NULL)
				rotateLeft(leaf->_left);
			rotateRight(leaf);
			if (leaf->_parent->_left->_right != _NULL)
				leaf->_parent->_left->_right->_color = BLACK_L;
		}
		else
		{
			if (leaf->_right->_left != _NULL)
				rotateRight(leaf->_right);
			rotateLeft(leaf);
			if (leaf->_parent->_right->_left != _NULL)
				leaf->_parent->_right->_left->_color = BLACK_L;
		}
		leaf->_parent->_color = BLACK_L;
	}

	void fixup_case_parent_black_child_red_grandchild_red_grandgrandchild_black(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			rotateRight(leaf);
			leaf->_parent->_color = BLACK_L;
			if (leaf->_left != _NULL)
				leaf->_left->_color = RED_L;
		}
		else
		{
			rotateLeft(leaf);
			leaf->_parent->_color = BLACK_L;
			if (leaf->_right != _NULL)
				leaf->_right->_color = RED_L;
		}
	}

	void fixup_case_all_black(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			leaf->_left->_color = RED_L;
			if (leaf->_parent != _NULL && leaf->_parent->_right == leaf)
				eraseFixup(leaf->_parent, 1);
			else if (leaf->_parent != _NULL)
				eraseFixup(leaf->_parent, 2);
		}
		else
		{
			leaf->_right->_color = RED_L;
			if (leaf->_parent != _NULL && leaf->_parent->_right == leaf)
				eraseFixup(leaf->_parent, 1);
			else if (leaf->_parent != _NULL)
			{
//				show();
				eraseFixup(leaf->_parent, 2);
			}
		}
	}


	bool condition_case_all_black(Node *leaf, std::string part)
	{

		if (part == "LEFT")
		{
			return ( leaf->_color == BLACK_L && leaf->_left != _NULL && leaf->_left->_color == BLACK_L &&
			(leaf->_left->_left == _NULL || leaf->_left->_left->_color == BLACK_L) &&
			(leaf->_left->_right == _NULL || leaf->_left->_right->_color == BLACK_L));
		}
		else
		{
			return ( leaf->_color == BLACK_L && leaf->_right != _NULL && leaf->_right->_color == BLACK_L &&
			(leaf->_right->_right == _NULL || leaf->_right->_right->_color == BLACK_L) &&
			(leaf->_right->_left == _NULL || leaf->_right->_left->_color == BLACK_L));
		}
	}

	bool condition_case_third(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			return (leaf->_color == BLACK_L && leaf->_left != _NULL && leaf->_left->_color == RED_L &&
			(  ( (leaf->_left->_left != _NULL && leaf->_left->_left->_left != _NULL && leaf->_left->_left->_left->_color == RED_L)  ||
			(leaf->_left->_left != _NULL && leaf->_left->_left->_right != _NULL && leaf->_left->_left->_right->_color == RED_L) )  ||
			 ( (leaf->_left->_right != _NULL && leaf->_left->_right->_left != _NULL && leaf->_left->_right->_left->_color == RED_L) ||
			 (leaf->_left->_right != _NULL && leaf->_left->_right->_right != _NULL && leaf->_left->_right->_right->_color == RED_L)  )  )  );
		}
		else
		{
			return (leaf->_color == BLACK_L && leaf->_right != _NULL && leaf->_right->_color == RED_L &&
			(  ( (leaf->_right->_right != _NULL && leaf->_right->_right->_right != _NULL && leaf->_right->_right->_right->_color == RED_L)  ||
			(leaf->_right->_right != _NULL && leaf->_right->_right->_left != _NULL && leaf->_right->_right->_left->_color == RED_L) )  ||
			( (leaf->_right->_left != _NULL && leaf->_right->_left->_right != _NULL && leaf->_right->_left->_right->_color == RED_L) ||
			(leaf->_right->_left != _NULL && leaf->_right->_left->_left != _NULL && leaf->_right->_left->_left->_color == RED_L)  )  )  );
		}
	}

	bool condition_case_forth(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			return (leaf->_color == BLACK_L && leaf->_left != _NULL && leaf->_left->_color == RED_L &&
			leaf->_left->_left != _NULL && leaf->_left->_right != _NULL &&
			(leaf->_left->_left->_left == _NULL && leaf->_left->_left->_right == _NULL &&
			leaf->_left->_right->_left == _NULL && leaf->_left->_right->_right == _NULL) );
		}
		else
		{
			return (leaf->_color == BLACK_L && leaf->_right != _NULL && leaf->_right->_color == RED_L &&
			leaf->_right->_right != _NULL && leaf->_right->_left != _NULL &&
			(leaf->_right->_right->_right == _NULL && leaf->_right->_right->_left == _NULL &&
			leaf->_right->_left->_right == _NULL && leaf->_right->_left->_left == _NULL) );
		}
	}

	bool conditional_case_fifth(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			return ( leaf->_color == BLACK_L && leaf->_left != _NULL && leaf->_left->_color == BLACK_L &&
			( (leaf->_left->_left != _NULL && leaf->_left->_left->_color == RED_L) ||
			(leaf->_left->_right != _NULL && leaf->_left->_right->_color == RED_L) ) );
		}
		else
		{
			return ( leaf->_color == BLACK_L && leaf->_right != _NULL && leaf->_right->_color == BLACK_L &&
			( (leaf->_right->_right != _NULL && leaf->_right->_right->_color == RED_L) ||
			(leaf->_right->_left != _NULL && leaf->_right->_left->_color == RED_L) ) );

		}
	}

	bool condition_case_second(Node *leaf, std::string part)
	{
		if (part == "LEFT")
		{
			return (leaf->_color == RED_L && leaf->_left != _NULL && leaf->_left->_color == BLACK_L &&
			(       (leaf->_left->_left != _NULL && leaf->_left->_left->_color == RED_L )
			|| (leaf->_left->_right != _NULL && leaf->_left->_right->_color == RED_L)    ));
		}
		else
		{
			return (leaf->_color == RED_L && leaf->_right != _NULL && leaf->_right->_color == BLACK_L &&
			(       (leaf->_right->_right != _NULL && leaf->_right->_right->_color == RED_L )
			|| (leaf->_right->_left != _NULL && leaf->_right->_left->_color == RED_L)    ));
		}
	}

	bool condition_case_first(Node *leaf, std::string part)
	{
		if (part == "LEFT")


			return (leaf->_color == RED_L && leaf->_left != _NULL &&
			leaf->_left->_color == BLACK_L && (   leaf->_left->_left == _NULL ||
			(leaf->_left->_left != _NULL && leaf->_left->_left->_color == BLACK_L)  ) && (    leaf->_left->_right == _NULL ||
			(leaf->_left->_right != _NULL && leaf->_left->_right->_color == BLACK_L)   ));
		else


			return (leaf->_color == RED_L && leaf->_right != _NULL &&
			leaf->_right->_color == BLACK_L && (    leaf->_right->_right == _NULL ||
			(leaf->_right->_right != _NULL && leaf->_right->_right->_color == BLACK_L)      ) && (     leaf->_right->_left == _NULL ||
			(leaf->_right->_left != _NULL && leaf->_right->_left->_color == BLACK_L)    ));
	}

	void eraseFixup(Node *leaf, int recursion = 0)
	{
		if (leaf->_right == _NULL || recursion == 1)
		{
			if (condition_case_first(leaf, "LEFT"))
				fixup_case_parent_red_child_black_grandchild_black(leaf, "LEFT");
			else if (condition_case_second(leaf, "LEFT"))
				fixup_case_parent_red_child_black_grandchild_red(leaf, "LEFT");
			else if (condition_case_third(leaf, "LEFT"))
				fixup_case_parent_black_child_red_grandchild_black_grandgranchild_red(leaf, "LEFT");
			else if (condition_case_forth(leaf, "LEFT"))
				fixup_case_parent_black_child_red_grandchild_red_grandgrandchild_black(leaf, "LEFT");
			else if (conditional_case_fifth(leaf, "LEFT"))
				fixup_case_parent_black_child_black_grandchild_red(leaf, "LEFT");
			else if (condition_case_all_black(leaf, "LEFT"))
				fixup_case_all_black(leaf, "LEFT");

		}
		else if (leaf->_left == _NULL || recursion == 2)
		{
			if (condition_case_first(leaf, "RIGHT"))
				fixup_case_parent_red_child_black_grandchild_black(leaf, "RIGHT");
			else if (condition_case_second(leaf, "RIGHT"))
				fixup_case_parent_red_child_black_grandchild_red(leaf, "RIGHT");
			else if (condition_case_third(leaf, "RIGHT"))
				fixup_case_parent_black_child_red_grandchild_black_grandgranchild_red(leaf, "RIGHT");
			else if (condition_case_forth(leaf, "RIGHT"))
				fixup_case_parent_black_child_red_grandchild_red_grandgrandchild_black(leaf, "RIGHT");
			else if (conditional_case_fifth(leaf, "RIGHT"))
				fixup_case_parent_black_child_black_grandchild_red(leaf, "RIGHT");
			else if (condition_case_all_black(leaf, "RIGHT"))
				fixup_case_all_black(leaf, "RIGHT");
		}

	}

	void case_black_leaf_zero_childs(Node *leaf)
	{
		if (leaf->_parent != _NULL)
		{
			if (leaf->_parent->_right == leaf)
				leaf->_parent->_right = _NULL;
			else
				leaf->_parent->_left = _NULL;
			eraseFixup(leaf->_parent);
		}
		else
			_root = _NULL;
		delete leaf;
	}

	void show(Node *leaf, int level)
	{
		if (leaf->_right != _NULL)
			show(leaf->_right, level + 1);
		for (int i = 0; i < level; ++i)
			std::cout << "       ";
		if (leaf->_color == RED_L)
			std::cout << RED << leaf->_pair.first << ":" << leaf->_pair.second << RESET << std::endl;
		else
			std::cout << GREEN << leaf->_pair.first << ":" << leaf->_pair.second << RESET << std::endl;
		if (leaf->_left != _NULL)
			show(leaf->_left, level + 1);
	}

	void delete_tree(Node *node)
	{
		if (node != _NULL)
		{
			delete_tree(node->_left);
			delete_tree(node->_right);
			delete node;
		}
	}

public:
	void show()
	{
		if (_root != _NULL)
			show(_root, 5);
	}

};

#endif