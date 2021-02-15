
#include "binary_tree.hpp"

int main()
{
	BinaryTree<int, double> tree;

	tree.insert(15, 7.23);

	tree.insert(78, 2.3);

	tree.insert(14, 12);

	tree.insert(22, 43.3);

	tree.insert(432, 324.32);

	tree.insert(300, 3.5);

	tree.insert(8, 12.12);
	//tree.show();
	tree.show();
}
