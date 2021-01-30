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
	std::list<int> list1;
	ft::list<int> lis1;


//	std::cout << allocator.max_size() / sizeof(int) << std::endl;


//	list1.assign(1, 10);
//	list1.assign(2, 11);
//	list1.assign(2, 15);

	int16_t a = 2;
	int b = 200;
	std::string str = "string";
	ft::list<int> list2(a, b);
	std::list<int> list(a, b);
	std::list<int>::iterator it = list.begin();

	std::list<int>::iterator iter = it;

	iter--;
	std::cout << *iter << std::endl;

	if (iter != it)
		std::cout << "go" << std::endl;
	ft::list<int> list3;


	return 0;
}
