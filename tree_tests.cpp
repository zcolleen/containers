
//#define MAP_ONLY
//#include "binary_tree.hpp"
#include "smth2.hpp"
#include <map>

int main()
{
	BinaryTree<int, double> tree;

	std::map<int, int> map;
	std::pair<int, int> pair(5, 89);

	map[2] = 2;
	map[15] = 4;
	map[10] = 10;

	map.insert(++++map.begin(), pair);

	if (map.count(5))
		std::cout << "jopa";

	std::map<int, int>::iterator it = map.begin();
//	std::map<int, int>::iterator end = map.end();
//
////	--it;
////	end;
//
	while (it != map.end())
	{
		std::cout << it->first << std::endl;
		++it;
	}

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

	tree.show();

}
