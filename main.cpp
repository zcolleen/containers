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
#define INDENT "      "


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
	std::cout << "      " + str;
	while (first != last)
	{
		std::cout <<  *first << " ";
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
	srand(time(NULL));

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

	std::cout << std::endl;
	std::cout << YELLOW << "Member functions: " << RESET << std::endl;

	ft_list_f = ft_list_ft;
	std_list_f = std_list_ft;

	comparison_print(ft_list_f, std_list_f, "Assignation operation: ");



	ft_list_f.assign(2, 42);
	std_list_f.assign(2, 42);

	comparison_print(ft_list_f, std_list_f, "Assign with count: ");

	ft_list_s.assign(ft_list_f.begin(), ft_list_f.end());
	std_list_s.assign(std_list_f.begin(), std_list_f.end());

	comparison_print(ft_list_s, std_list_s, "Assign with iterators: ");

	ft_list_f.push_front(84);
	std_list_f.push_front(84);

	comparison_print(ft_list_f, std_list_f, "Pushing front: ");

	std::cout << RED << "      Front value is: " << ft_list_f.front() << RESET << std::endl;
	std::cout << GREEN << "      Front value is: " << std_list_f.front() << RESET << std::endl;

	ft_list_s.push_back(52);
	std_list_s.push_back(52);

	comparison_print(ft_list_s, std_list_s, "Pushing back: ");

	std::cout << RED << "      Back value is: " << ft_list_s.back() << RESET << std::endl;
	std::cout << GREEN << "      Back value is: " << std_list_s.back() << RESET << std::endl;

	std::cout << std::endl;
	std::cout << YELLOW << "Iterators: " << RESET << std::endl;

	ft::list<size_t>::iterator ft_iter = ft_list_ft.begin();
	ft::list<size_t>::iterator ft_iter_end = ft_list_ft.end();

	std::list<size_t>::iterator std_iter = std_list_ft.begin();

	while (ft_iter != ft_iter_end)
	{
		*ft_iter = rand() % 100;
		*std_iter = *ft_iter;
		++ft_iter;
		++std_iter;
	}

	comparison_print(ft_list_ft, std_list_ft, "Filling array with iterators: ");

	ft::list<size_t>::const_reverse_iterator ft_iter_r = ft_list_ft.rbegin();
	ft::list<size_t>::const_reverse_iterator ft_iter_r_end = ft_list_ft.rend();

	std::list<size_t>::const_reverse_iterator std_iter_r = std_list_ft.rbegin();
	std::list<size_t>::const_reverse_iterator std_iter_r_end = std_list_ft.rend();

	std::cout << RED << "      Reverse iterator: ";
	while (ft_iter_r != ft_iter_r_end)
	{
		std::cout << " " << *ft_iter_r;
		ft_iter_r++;
	}
	std::cout << RESET << std::endl;

	std::cout << GREEN << "      Reverse iterator: ";
	while (std_iter_r != std_iter_r_end)
	{
		std::cout << " " << *std_iter_r;
		std_iter_r++;
	}
	std::cout << RESET << std::endl;

	ft::list<size_t>::const_iterator ft_iter_c = ft_list_ft.begin();
	ft::list<size_t>::const_iterator ft_iter_c_end = ft_list_ft.end();

	std::list<size_t>::const_iterator std_iter_c = std_list_ft.begin();
	std::list<size_t>::const_iterator std_iter_c_end = std_list_ft.end();

	std::cout << RED << "      Const straight iterator: ";
	while (ft_iter_c != ft_iter_c_end)
	{
		std::cout << " " << *ft_iter_c;
		ft_iter_c++;
	}
	std::cout << RESET << std::endl;

	std::cout << GREEN << "      Const straight iterator: ";
	while (std_iter_c != std_iter_c_end)
	{
		std::cout << " " << *std_iter_c;
		std_iter_c++;
	}
	std::cout << RESET << std::endl;

	std::cout << std::endl;
	std::cout << YELLOW << "Test with elements of list: " << RESET << std::endl;
	std::cout << RED << "      Checking if third container is empty: " << ft_list_t.empty() << RESET << std::endl;
	std::cout << GREEN << "      Checking if third container is empty: " << std_list_t.empty() << RESET << std::endl;

	std::cout << RED << "      Size of container: " << ft_list_t.size() << RESET << std::endl;
	std::cout << GREEN << "      Size of container: " << std_list_t.size() << RESET << std::endl;

	std::cout << RED << "      Clearing containers" << RESET << std::endl;
	ft_list_t.clear();
	std::cout << GREEN << "      Clearing containers" << RESET << std::endl;
	std_list_t.clear();

	std::cout << RED << "      Checking again if third container is empty: " << ft_list_t.empty() << RESET << std::endl;
	std::cout << GREEN << "      Checking again if third container is empty: " << std_list_t.empty() << RESET << std::endl;

	std::cout << RED << "      Size of container: " << ft_list_t.size() << RESET << std::endl;
	std::cout << GREEN << "      Size of container: " << std_list_t.size() << RESET << std::endl;

	std::cout << RED << "      Max size: " << ft_list_t.max_size() << RESET << std::endl;
	std::cout << GREEN << "      Max size: " << std_list_t.max_size() << RESET << std::endl;



}