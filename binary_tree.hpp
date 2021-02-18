

#ifdef MAP_ONLY
//#undef MAP_ONLY
#ifndef CONTAINERS_BINARY_TREE_HPP
#define CONTAINERS_BINARY_TREE_HPP
#define BLACK_L false
#define RED_L true
#define RED "\033[1;31m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"

#include <iostream>

template< class Key, class T, class Compare = std::less<Key> >
class BinaryTree {

public:

	typedef struct Node {

		Node() : _parent(NULL), _right(NULL), _left(NULL), _color(BLACK_L) {}

		Node(const Key &key, const T &value, struct Node *node) : _key(key), _value(value), _parent(node), _right(node),
		_left(node), _color(RED_L) {}
		Key			_key;
		T			_value;
		struct Node *_parent;
		struct Node *_right;
		struct Node *_left;
		bool 		_color;
	}				Node;

	Node *_NULL;
	Node *_root;
	Compare _comparator;
	bool _is_key_repeated;

	explicit BinaryTree(bool repeat = false) : _NULL(new Node), _root(_NULL), _is_key_repeated(repeat) {}
	~BinaryTree() {
		delete_tree(_root);
	//	delete _NULL;
	}

	void insert(const Key &key, const T &value)
	{
		if (_root == _NULL)
		{
			_root = new Node(key, value, _NULL);
			_root->_color = BLACK_L;
		}
		else
			insert(key, value, _root);

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

	void insert(const Key &key, const T &value, Node *leaf)
	{
		while (leaf != _NULL)
		{
			if (!_comparator(key, leaf->_key) && !_comparator(leaf->_key, key))
			{
				leaf->_value = value;
				break;
			}
			else if (_comparator(key, leaf->_key))
			{
				if (leaf->_left != _NULL)
					leaf = leaf->_left;
				else
				{
					leaf->_left = new Node(key, value, _NULL);
					leaf->_left->_parent = leaf;
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
					insertFixup(leaf->_right);
					break;
				}
			}
		}
	}

	void delete_node(const Key &key)
	{
		delete_node(key, _root);
	}

	void delete_node(const Key &key, Node *leaf)
	{
		while (leaf != _NULL)
		{
			if (!_comparator(key, leaf->_key) && !_comparator(leaf->_key, key))
			{
				delete_node(leaf);
				break;
			}
			else if (_comparator(key, leaf->_key))
				leaf = leaf->_left;
			else
				leaf = leaf->_right;
		}
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

		T tmp_val = max_left_element->_value;
		Key tmp_key = max_left_element->_key;
		max_left_element->_value = leaf->_value;
		leaf->_value = tmp_val;
		max_left_element->_key = leaf->_key;
		leaf->_key = tmp_key;
		if (max_left_element->_color == RED_L)
			case_red_leaf_zero_childs(max_left_element);
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
//			std::cout << leaf->_parent->_key << std::endl;
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

	void show()
	{
		if (_root != _NULL)
			show(_root, 5);
	}

	void show(Node *leaf, int level)
	{
		if (leaf->_right != _NULL)
			show(leaf->_right, level + 1);
		for (int i = 0; i < level; ++i)
			std::cout << "       ";
		if (leaf->_color == RED_L)
			std::cout << RED << leaf->_key << ":" << leaf->_value << RESET << std::endl;
		else
			std::cout << GREEN << leaf->_key << ":" << leaf->_value << RESET << std::endl;
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
};


#endif
#endif