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

bool p(const int &a, const int &b)
{
	return (a < b);
}

int main()
{
	int a = 0;

	ft::list<int> list(a, 10);
	std::list<int> list_def(a, 10);
	std::vector<int> vector(4, 3);

	ft::list<int> list2(vector.begin(), vector.end());




	list.push_front(16);
	list.push_front(15);
	list.push_front(14);
	list.push_front(13);
	list.push_front(12);
	list_def.push_front(16);
	list_def.push_front(15);
	list_def.push_front(14);
	list_def.push_front(13);
	list_def.push_front(12);
	list.clear();
	list.push_back(4);
	list.push_back(4);
	list.push_back(19);
	list.push_back(20);
	list.push_back(20);
	list.push_back(20);
	list.push_back(21);

	std::cout << "Size: " << list.size() << std::endl;

	list.unique();
	print(list.begin(), list.end(), "Ascending: ");
//	list.sort(std::less<int>());
//	list_def.sort();
//	print(list_def.begin(), list_def.end(), "Def list sorted: ");
//	list_def.sort(std::less<int>());
//	print(list.begin(), list.end(), "Descending sort: ");
//	print(list_def.begin(), list_def.end(), "Def list: ");
	return 0;
}
