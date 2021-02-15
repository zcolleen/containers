

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

		Node(const Key &key, const T &value) : _key(key), _value(value), _parent(NULL), _right(NULL),
		_left(NULL), _color(RED_L) {}
		Key			_key;
		T			_value;
		struct Node *_parent;
		struct Node *_right;
		struct Node *_left;
		bool 		_color;
	}				Node;

	Node *_root;
	Compare _comparator;
	bool _is_key_repeated;

	BinaryTree(bool repeat = false) : _root(NULL), _is_key_repeated(repeat) {}
	~BinaryTree() { delete_tree(_root); }

	void insert(const Key &key, const T &value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
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
		if (child->_right != NULL)
			child->_right->_parent = leaf;
		child->_parent = leaf->_parent;

		if (leaf->_parent)
		{
			if (leaf == leaf->_parent->_right)
				leaf->_parent->_right = child;
			else
				leaf->_parent->_left = child;
		}
		else
			_root = child;

		child->_right = leaf;
		leaf->_parent = child;
	}

	void rotateLeft(Node *leaf)
	{
		//априорно существует ребенок
		Node *child = leaf->_right;

		leaf->_right = child->_left;
		if (child->_left != NULL)
			child->_left->_parent = leaf;
		child->_parent = leaf->_parent;

		if (leaf->_parent)
		{
			if (leaf == leaf->_parent->_left)
				leaf->_parent->_left = child;
			else
				leaf->_parent->_right = child;
		}
		else
			_root = child;

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
				if (uncle && uncle->_color == RED_L)
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
				if (uncle && uncle->_color == RED_L)
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
		while (leaf != NULL)
		{
			if (!_is_key_repeated && !_comparator(key, leaf->_key) && !_comparator(leaf->_key, key))
			{
				leaf->_value = value;
				break;
			}
			else if (_comparator(key, leaf->_key))
			{
				if (leaf->_left != NULL)
					leaf = leaf->_left;
				else
				{
					leaf->_left = new Node(key, value);
					leaf->_left->_parent = leaf;
					insertFixup(leaf->_left);
					break;
				}
			}
			else
			{
				if (leaf->_right != NULL)
					leaf = leaf->_right;
				else
				{
					leaf->_right = new Node(key, value);
					leaf->_right->_parent = leaf;
					insertFixup(leaf->_right);
					break;
				}
			}
		}
	}

	void show()
	{
		show(_root, 10);
	}

	void show(Node *leaf, int level)
	{
		if (leaf->_right)
			show(leaf->_right, level + 1);
		for (int i = 0; i < level; ++i)
			std::cout << "     ";
		if (leaf->_color == RED_L)
			std::cout << RED << leaf->_key << ":" << leaf->_value << RESET << std::endl;
		else
			std::cout << GREEN << leaf->_key << ":" << leaf->_value << RESET << std::endl;
		if (leaf->_left)
			show(leaf->_left, level + 1);
	}


	void print()
	{
		print(_root, 10);
	}

	void print(Node *leaf, int level)
	{
		bool in_right = false;

		for (int ix = 0; ix < level; ++ix)
			std::cout << ' ';
		std::cout << leaf->_key << ":" << leaf->_value << std::endl;
		if (leaf->_left)
		{
			in_right = true;
			level -= 2;
			std::cout << std::endl;
			print(leaf->_left, level);
		}
		if (leaf->_right)
		{
			if (!in_right)
				std::cout << std::endl;
			level += 2;
			print(leaf->_right, level);
		}
	}

	void delete_tree(Node *node)
	{
		if (node != NULL)
		{
			delete_tree(node->_left);
			delete_tree(node->_right);
			delete node;
		}
	}
};


#endif
