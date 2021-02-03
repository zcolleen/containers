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


template <typename T>
void print(T first, T last)
{
	while (first != last)
	{
		std::cout << *first << " ";
		first++;
	}
	std::cout << std::endl;
}


template <typename T>
void print(T first, T last, std::string str)
{
	std::cout << str;
	while (first != last)
	{
		std::cout << *first << " ";
		first++;
	}
	std::cout << std::endl;
}

int main()
{
	int a = 0;

	ft::list<int> list(a, 10);
	std::vector<int> vector(4, 3);

	ft::list<int> list2(vector.begin(), vector.end());
	ft::list<int>::iterator it = list.begin();
//	ft::list<int>::iterator iter = list2.begin();
//	ft::list<int>::iterator pos = it;



	list.push_front(29);
	list.push_back(12);
	list.push_back(18);
	list.push_back(87);
	list.push_front(77);


	std::cout << "Size: " << list.size() << std::endl;

	it = list.begin();
	print(it, list.end(), "List: ");
//	la.erase(la.end());
	list2.resize(1, 7);
	ft::list<int>::iterator i = list2.begin();
	ft::list<int>::iterator i_end = list2.end();
	print(i, i_end, "List2: ");
	list2.swap(list);
	print(list2.begin(), list2.end(), "List2: ");
	print(list.begin(), list.end(), "List: ");
	list2.reverse();
//	list2.reverse();
	print(list2.begin(), list2.end(), "Reversed list: ");
	list2.sort();
	print(list2.begin(), list2.end(), "Sorted list: ");
//	print(iter, list2.end());
	return 0;
}
