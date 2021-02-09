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
	std::vector<size_t> v(8, 11);
	ft::vector<size_t> in(2, 22);


	in.reserve(10);
	in.insert(in.begin(), 10);

	print(in.begin(), in.end(), "Victor: ");

	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;

	in.insert(in.begin(), 42);

	print(in.begin(), in.end(), "Victor: ");

	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;
	in.insert(in.begin(), 10, 32);
	print(in.begin(), in.end(), "Victor: ");
	std::cout << "Capacity: " << in.capacity() << " Size: " << in.size() << std::endl;

//	v.insert(--v.begin(), 19);

	return 0;
}
