#include <iostream>
#include "list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "vector.hpp"
#include <vector>
#include <stack>
#include <queue>
#include <list>

#define YELLOW  "\033[1;33m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"
#define STD true
#define FT false



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
void print(T first, T last, std::string str, bool colour)
{
	if (colour == STD)
		std::cout << GREEN;
	else
		std::cout << RED;
	std::cout << str;
	while (first != last)
	{
		std::cout << *first << " ";
		first++;
	}
	std::cout << RESET;
	std::cout << std::endl;
}

template <typename DEF, typename MY>
void comparison_print(DEF _std, MY _ft, std::string str)
{
	print(_std.begin(), _std.end(), str, FT);
	print(_ft.begin(), _ft.end(), str, STD);
}

int main()
{
	//list tests

	std::cout << YELLOW << "List constructors: " << RESET << std::endl;

	ft::list<size_t> ft_list_f;
	std::list<size_t> std_list_f;

	ft::list<size_t> ft_list_s(5, 21);
	std::list<size_t> std_list_s(5, 21);

	comparison_print(ft_list_s, std_list_s, "Range constructor: ");

	ft::list<size_t> ft_list_t(ft_list_s.begin(), ft_list_s.end());
	std::list<size_t> std_list_t(std_list_s.begin(), std_list_s.end());

	comparison_print(ft_list_t, std_list_t, "Iterator constructor: ");

	ft::list<size_t> ft_list_ft(ft_list_t);
	std::list<size_t> std_list_ft(std_list_t);

	comparison_print(ft_list_ft, std_list_ft, "Copy constructor: ");

	ft_list_f = ft_list_ft;
	std_list_f = std_list_ft;

	comparison_print(ft_list_f, std_list_f, "Assignation operation: ");

	std::cout << std::endl;

}