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
	void scream(){
		std::cout << "Suka" << std::endl;
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
	ft::vector<size_t> vector(13, 13);
	ft::vector<size_t> def_vector(13, 13);
	ft::vector<int> vect(4, 123);
	ft::vector<int> vector1(6, 10);

	int64_t  *a = NULL;
	--a;
	std::cout << a << std::endl;
//	ft::vector<int>::iterator it = vect.end();
//	it--;
//	size_t f = it - vect.begin();
//	std::cout << f << std::endl;
	ft::vector<int>::iterator it = vect.begin();
	ft::vector<int>::iterator end = vect.end();
	ft::vector<int>::iterator add;
	        //	end = end - 1;
////	std::cout << *(end - it);
	std::cout << "Vector: ";
	while (it != end)
	{
		std::cout << " " << *it;
		if (it < end)
			std::cout << "bla";
		add = 2 + it;
		it = add;
	}
	if (it > end)
		std::cout << "llldldlldl";
	std::cout << std::endl;
	return 0;
}
