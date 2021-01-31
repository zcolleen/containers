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
	ft::list<int> a((size_t)1, 10);
	ft::list<int>::iterator it = a.begin();

	while (true)
	{
//		std::cout << *it << std::endl;
		it++;
	}
	return 0;
}
