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

	ft::list<int> list;
	std::vector<int> vector(4, 3);

	ft::list<int> list2(vector.begin(), vector.end());
	ft::list<int> l(10, 15);

//	list.push_back(12);
//	list.push_back(13);
//	list.push_back(22);
	list2.clear();
	list2.push_back(102);
	list2.push_back(104);
//	list.push_back(90);

//	list2.push_back(110);
//	list2.push_back(120);

//	print(list.begin(), list.end(), "First list before splice: ");
//	print(list2.begin(), list2.end(), "Second list before splice: ");

	list.splice(list.begin(), list2, list2.begin());
	list.splice(list.begin(), list2, list2.begin());
//	print(list.begin(), list.end(), "After splice first list: ");
//	print(list2.begin(), list2.end(), "After splice second list: ");

	list2.clear();
	list.clear();
//	list2.push_back(12);
//	list2.push_back(10);
//	list.push_front(10);
//	list.push_front(12);
	std::list<int> a;
	std::list<int> b;

	a.push_back(10);
	a.push_back(20);
	a.push_back(16);

	b.push_back(10);
	b.push_back(20);
	b.push_back(15);
	b.push_back(89);


	if (a > b)
	{
		std::cout << "More" << std::endl;
	}
	if (a < b) {
		std::cout << "Less" << std::endl;
	}
	if (a <= b) {
		std::cout << "Less or eq" << std::endl;
	}
	if (a >= b) {
		std::cout << "More or eq" << std::endl;
	}

	return 0;
}
