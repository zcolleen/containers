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
	ft::list<int> a;
	ft::list<int> b;

	a.push_back(10);
	a.push_back(20);
	a.push_back(16);

	a.sort();
	b.push_back(10);
	b.push_back(20);
	b.push_back(-100);
//	b.push_back(89);
	b.sort();
	print(a.begin(), a.end(), "Sorted first: ");
	print(b.begin(), b.end(), "Sorted second: ");

	a.splice(a.begin(), b, ++b.begin(), --b.end());
	print(a.begin(), a.end(), "Spliced first: ");
	print(b.begin(), b.end(), "Spliced second: ");


	ft::list<int>::iterator str_iter = a.begin();
	ft::list<int>::iterator str_end = a.end();
	ft::list<int>::reverse_iterator reve_iter = a.rbegin();
	ft::list<int>::reverse_iterator reve_end = a.rend();

	std::cout << "Straight: ";
	while (str_iter != str_end)
	{
		std::cout << *str_iter << " ";
		str_iter++;
	}
	std::cout << std::endl;

	std::cout << "Reversed: ";
	while (reve_iter != reve_end)
	{
		std::cout << *reve_iter << " ";
		reve_iter++;
	}
	std::cout << std::endl;
	return 0;
}
