
//#define MAP_ONLY
#include "binary_tree.hpp"
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
	BinaryTree<int, double> tree(true);

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

#define SIZE 10000

	int *values = new int[SIZE];

	for (int i = 0; i < SIZE; ++i)
	{
		*(values + i) = rand() % 1000;
		std::cout << *(values + i) << std::endl;
		tree.insert(*(values + i), 17);
	}
//	debug_show(tree);

//	std::cout << tree.tree_size() << std::endl;
	std::cout << "//////////END OF INSERTION/////////" << std::endl;
//	tree.delete_node(0);

//	debug_show(tree);

	int *size_a = new int[SIZE];

	for (int i = 0; i < SIZE; ++i)
	{
//		std::cout << *(values + i) << std::endl;
//		tree.delete_node(*(values + i));
//		*(size_a + i) = tree.tree_size();
//		std::cout << "Value: " << *(values + i) << "Size: " << *(size_a + i) << std::endl;
		tree.delete_node(*(values + i));
//		std::cout << RED << i << RESET << std::endl;
		//debug_show(tree);
	}

	bool success = true;
	for (int i = 1; i < SIZE; ++i)
	{
		if (*(size_a + i - 1) != *(size_a + i) + 1)
		{
			success = false;
			break;
		}
	}
	std::cout << "end" << std::endl;
//	if (success)
//		std::cout << "success" << std::endl;
//	else
//		std::cout << "failure" << std::endl;
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
