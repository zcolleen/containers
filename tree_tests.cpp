
//#define MAP_ONLY
//#include "binary_tree.hpp"
#include "smth2.hpp"
#include <map>

int main()
{
	BinaryTree<int, double> tree;

	tree.insert(18, 7.23);

	tree.insert(78, 2.3);

	tree.insert(14, 12);

	tree.insert(22, 43.3);

	tree.insert(432, 324);

	tree.insert(10, 3.5);

	//tree.insert(15, 12.12);

	tree.insert(12, 32.32);

	tree.insert(300, 32);

	tree.insert(280, 3);

	tree.insert(14, 19);

//	tree.show();

	std::cout << std::endl << std::endl;

	tree.delete_node(18);

//	tree.show();

	BinaryTree<int, double> new_tree;

	new_tree.insert(15, 17);

	new_tree.insert(10, 12);

	new_tree.insert(28, 21);

	new_tree.insert(29, 1);

	new_tree.insert(13, 12);

	new_tree.show();

	std::cout << std::endl << std::endl;

	new_tree.delete_node(10);

	new_tree.show();

}
