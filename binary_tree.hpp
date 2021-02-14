

#ifndef CONTAINERS_BINARY_TREE_HPP
#define CONTAINERS_BINARY_TREE_HPP
#define BLACK_L false
#define RED_L true

template< class Key, class T, class Compare = std::less<Key> >
class BinaryTree {

public:

	typedef struct Node {

		Node(const Key &key, const T &value) : _key(key), _value(value), _parent(NULL), _right(NULL),
		_left(NULL), _color(BLACK_L) {}
		Key			_key;
		T			_value;
		struct Node *_parent;
		struct Node *_right;
		struct Node *_left;
		bool 		_color;
	}				Node;

	Node *_root;
	Compare _comparator;

	BinaryTree() : _root(NULL) {}
	~BinaryTree() { delete_tree(_root); }

	void insert(const Key &key, const T &value)
	{
		if (_root == NULL)
			_root = new Node(key, value);
		else
			insert(key, value, _root);

	}

	void insert(const Key &key, const T &value, Node *leaf)
	{
		while (leaf != NULL)
		{
			if (_comparator(key, leaf->_key))
			{
				if (leaf->_left != NULL)
					leaf = leaf->_left;
				else
				{
					leaf->_left = new Node(key, value);
					leaf->_left->_parent = leaf;
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
					break;
				}
			}
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
