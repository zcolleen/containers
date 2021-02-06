#include <iostream>
#include <list>
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include <vector>
#include <stack>
#include <queue>

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

	Some_class(const Some_class &obj) {

		ptr = new int[10];
		std::cout << "constructor copy" << std::endl;
		for (int i = 0; i < 10; ++i)
			ptr[i] = obj.ptr[i];
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
	std::vector<int> vector;
	vector.push_back(10);
	vector.push_back(98);
	std::vector<int>::iterator it = vector.end();
	--it;
	std::vector<int>::iterator beg = vector.begin();
	--beg;

	while (it != beg)
	{
	//	std::cout << *it << std::endl;
		std::cout << *it << std::endl;
		--it;
	}
	return 0;
}
