
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

#define SIZE 500

	int *values = new int[SIZE];

//	*(values) = 124;
//	*(values + 1) = 646;
//	*(values + 2) = 890;
//	*(values + 3) = 472;
//	*(values + 4) = 894;
//	*(values + 5) = 384;
//	*(values + 6) = 842;
//	*(values + 7) = 125;
//	*(values + 8) = 300;
//	*(values + 9) = 246;
//	*(values + 10) = 286;
//	*(values + 11) = 995;
//	*(values + 12) = 673;
//	*(values + 13) = 161;
//	*(values + 14) = 478;
//	*(values + 15) = 667;
	for (int i = 0; i < SIZE; ++i)
	{
		*(values + i) = rand() % 1000;
		std::cout << *(values + i) << std::endl;
		tree.insert(*(values + i), 17);
	}
	debug_show(tree);

	std::cout << "/////////////////END OF INSERTION/////////" << std::endl;
//	tree.delete_node(0);

	debug_show(tree);
	for (int i = 0; i < SIZE; ++i)
	{
//		std::cout << *(values + i) << std::endl;
//		tree.delete_node(*(values + i));
		std::cout << *(values + SIZE - 1 - i) << std::endl;
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
