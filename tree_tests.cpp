
//#define MAP_ONLY
//#include "binary_tree.hpp"
#include "smth2.hpp"
#include <map>

template <class T, class E>
void debug_show(BinaryTree<T, E> &tree)
{
	tree.show();
	std::cout << std::endl << std::endl;
}



int main()
{
	srand(time(NULL));
	BinaryTree<int, double> tree;

	tree.insert(18, 7.23);

	tree.insert(78, 2.3);

	tree.insert(14, 12);

	tree.insert(22, 43.3);

	tree.insert(432, 324);

	tree.insert(10, 3.5);

	//tree.insert(15, 12.12);

	//tree.insert(12, 32.32);

	tree.insert(300, 32);

	tree.insert(280, 3);

//	tree.insert(14, 19);

	tree.insert(435, 0);

	tree.insert(12, 3);


	debug_show(tree);

	tree.delete_node(22);

	debug_show(tree);

	tree.delete_node(12);

	debug_show(tree);

	tree.delete_node(18);

	debug_show(tree);

	tree.delete_node(14);

	debug_show(tree);

	tree.delete_node(10);

	debug_show(tree);

	tree.delete_node(78);

	debug_show(tree);

	tree.delete_node(280);

	debug_show(tree);

	tree.delete_node(300);

	debug_show(tree);

	tree.delete_node(432);

	debug_show(tree);

	tree.delete_node(435);

	debug_show(tree);

#define SIZE 16

	int *values = new int[SIZE];

	for (int i = 0; i < SIZE; ++i)
	{
		*(values + i) = i;/*rand() % 100;*/
		tree.insert(*(values + i), 17);
	}
	debug_show(tree);

//	tree.delete_node(0);

	debug_show(tree);
	for (int i = 0; i < SIZE; ++i)
	{
		tree.delete_node(*(values + SIZE - 1 - i));
//		std::cout << RED << i << RESET << std::endl;
		debug_show(tree);
	}

//	debug_show(tree);
//	BinaryTree<int, double> new_tree;
//
//	new_tree.insert(15, 17);
//
//	new_tree.insert(10, 12);
//
//	new_tree.insert(28, 21);
//
//	new_tree.insert(29, 1);
//
//	new_tree.insert(13, 12);
//
//	new_tree.show();
//
//	std::cout << std::endl << std::endl;
//
//	new_tree.delete_node(10);
//
//	new_tree.show();

}
