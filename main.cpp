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


//	std::allocator<Some_class> allocator;
//	ft::list<int> list(10, 20);
//	std::list<int> list1(static_cast<size_t>(first), static_cast<value_type>(last));
//	std::list<int>::iterator it = list1.begin();

	std::vector<int> f(10);

	std::list<int> list1(f.begin(), f.end());
//	ft::list<int> list(10, 0);
	ft::list<int> l(f.begin(), f.end());

//	std::vector<int> a(10, 30);
//
//	std::vector<int>::iterator it = a.begin();
//
//	std::list<int> list2(it, a.end());
//
//	std::cout << *list2.begin() << std::endl;


	return 0;
}
