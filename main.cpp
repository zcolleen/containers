#include <iostream>
#include <list>
#include "list.hpp"
#include <vector>


class Some_class {


public:

	int *ptr;
	Some_class()
	{
		ptr = new int[10];
		std::cout << "constructor" << std::endl;
		for (int i = 0; i < 10; ++i)
			ptr[i] = i;
	}

	Some_class(int a)
	{
		ptr = new int[a];
		std::cout << "constructor2" << std::endl;
		for (int i = 0; i < a; ++i)
			ptr[i] = a;
	}

	Some_class(int a, int b)
	{
		ptr = new int[a];
		std::cout << "constructor3" << std::endl;
		ptr[0] = b;
//		ptr[1] = c;
//		ptr[2] = d;
//		ptr[3] = e;
	}

	~Some_class(){

		std::cout << "destructor" << std::endl;
		delete ptr;
	}
};




int main()
{
	int a = 0;

	ft::list<int> list(a, 10);
	std::vector<int> vector(4, 3);

	std::list<int> la(vector.begin(), vector.end());

	ft::list<int> list2(vector.begin(), vector.end());
	ft::list<int>::iterator it = list.begin();
	ft::list<int>::iterator iter = list2.begin();
	ft::list<int>::iterator pos = it;
//	pos++;
//	pos++;
//	pos++;

//	list.insert(pos, 1, 7);
//	list.push_front(26);
	list.push_front(29);
//	pos = list.begin();
	list.push_back(12);
	list.push_back(18);

	pos = list.begin();
	
	pos++;
	pos = list.erase(pos, list.end());
	std::cout << "Size: " << list.size() << std::endl;

	it = list.begin();
	while (it != list.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
//	la.erase(la.end());
	while (iter != list2.end())
	{
		std::cout << *iter << " ";
		iter++;
	}
	std::cout << std::endl;
// 	ft::list<int> a((size_t)0, 10);
// 	std::list<int> b((size_t)0, 10);
// 	ft::list<int>::iterator it = a.begin();
// //	ft::list<int>::iterator it_end = a.end();
// 	std::list<int>::iterator iter;


// 	//it++;
// //	it++;
// 	it = a.insert(it, 5);
// 	std::cout << "Size: " << a.size() << std::endl;
// //	it = a.begin();
// 	while (it != a.end())
// 	{
// 		std::cout << *it << std::endl;
// 		it++;
// 	}
	return 0;
}
