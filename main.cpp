#include <iostream>
#include <list>
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "vector.hpp"
#include <vector>
#include <stack>
#include <queue>

class Some_class {


public:

	int *ptr;
	int _a;
	Some_class()
	{
		ptr = new int[10];
		std::cout << "constructor" << std::endl;
		for (int i = 0; i < 10; ++i)
			ptr[i] = i;
	}

	Some_class(const Some_class &obj) {

		_a = obj._a;
		ptr = new int[_a];
		std::cout << "constructor copy" << std::endl;
		for (int i = 0; i < _a; ++i)
			ptr[i] = obj.ptr[i];
	}
	Some_class(int a)
	{
		_a = a;
		ptr = new int[a];
		std::cout << "constructor2" << std::endl;
		for (int i = 0; i < a; ++i)
			ptr[i] = a;
	}
	void scream(){
		std::cout << "Suka" << std::endl;
	}
	~Some_class(){

		std::cout << "destructor" << std::endl;
		delete ptr;
	}
	friend std::ostream& operator<< (std::ostream &out, const Some_class &point) {

		out << "A: " << point._a;
		return (out);
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
	ft::vector<size_t> in(2, 22);
//	ft::list<size_t> list(1, 87);

	in.reserve(2);
//	in.insert(++in.begin(), list.begin(), list.end());
	in.insert(in.begin(), 10);

	print(in.begin(), in.end(), "Victor: ");

	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;

	in.insert(++in.begin(), 42);

	print(in.begin(), in.end(), "Victor: ");

	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;
	in.insert(in.end(), 1, 32);
	print(in.begin(), in.end(), "Victor: ");
	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;

	in.push_back(321);
	in.push_back(456);
	in.push_back(987);


	print(in.begin(), in.end(), "Vitynya: ");


	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;

	in.clear();
	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;
	print(in.begin(), in.end(), "Vitynya: ");
	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;
	in.push_back(23);
	in.push_back(25);
	in.push_back(48);
	in.push_back(987);
	in.push_back(567);
	in.push_back(742);
//	//in.erase(++++in.begin(), ----in.end());
//
	print(in.begin(), in.end(), "Vitynya: ");

//
	in.erase(in.begin());
//
	print(in.begin(), in.end(), "Vitynya: ");

	in.erase(in.begin());
//
	print(in.begin(), in.end(), "Vitynya: ");

	ft::vector<size_t>::iterator it = in.erase(++in.begin(), --in.end());

	std::cout << *it << std::endl;
	in.erase(in.begin());
	print(in.begin(), in.end(), "Vitynya: ");
	in.pop_back();
	print(in.begin(), in.end(), "Vitynya: ");
	in.push_back(128);
	in.push_back(228);
	print(in.begin(), in.end(), "Vitynya: ");
	in.erase(++in.begin(), ++in.begin());
	print(in.begin(), in.end(), "Vitynya: ");

	in.resize(6, 322);
	print(in.begin(), in.end(), "Vitynya: ");

	in.resize(3, 552);

	print(in.begin(), in.end(), "Vitynya: ");


	ft::list<std::string> list(2, "nastya");

	list.resize(6, "sema");

	print(list.begin(), list.end(), "Sweden family: ");


	list.resize(7, "fsokdf");

	print(list.begin(), list.end(), "Sweden family: ");


	ft::list<int>  s(3, 2);
	ft::list<int>  d(4, 5);

	s.splice(++s.begin(), d);

	print(s.begin(), s.end(), "Go: ");

	d.push_back(12);

	d.push_back(214);

	print(d.begin(), d.end(), "Went: ");

	d.pop_back();

	print(d.begin(), d.end(), "Went: ");

	ft::swap(d, s);


	print(d.begin(), d.end(), "Went: ");

	print(s.begin(), s.end(), "Go: ");


	if (s != d)
		std::cout << "dfklns" << std::endl;
	return 0;
}

//int main()
//{
//	ft::list<size_t> l(1, 19);
//	ft::vector<size_t> v(10, 12);
//
//	v.clear();
//
//	print(l.begin(), l.end(), "fuygasfidj ");
//}