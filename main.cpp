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
void comparison_print(MY _ft, DEF _std, std::string str)
{
	print(_ft.begin(), _ft.end(), str, FT);
	print(_std.begin(), _std.end(), str, STD);
}


typedef struct unaryPredicate {
		unaryPredicate() {};
		bool operator()(int a) { return (a % 2 == 0); }
	}			unaryPredicate;

bool binaryPredicate(int a, int b) {
	return (b > a + 10);
}

void list_tests()
{
	std::cout << BLUE << "///////////////////////LIST TESTS///////////////////////" << RESET << std::endl;
	std::cout << std::endl;
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

	size_t value;
	while (ft_iter != ft_iter_end)
	{
		value = rand() % 100;
		*ft_iter = value;
		*std_iter = value;
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
	std::cout << YELLOW << "Test with size of list: " << RESET << std::endl;
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

	std::cout << std::endl;
	std::cout << YELLOW << "Test with elements of list: " << RESET << std::endl;

	comparison_print(ft_list_ft, std_list_ft, "Fourth list: ");

	ft_list_ft.insert(++ft_list_ft.begin(), 2, 24);
	std_list_ft.insert(++std_list_ft.begin(), 2, 24);

	comparison_print(ft_list_ft, std_list_ft, "Inserting two elements after begin element: ");

	ft_list_ft.insert(ft_list_ft.begin(), 64);
	std_list_ft.insert(std_list_ft.begin(),  64);

	comparison_print(ft_list_ft, std_list_ft, "Inserting one element before begin: ");

	ft_list_ft.insert(ft_list_ft.end(), ft_list_s.begin(), ft_list_s.end());
	std_list_ft.insert(std_list_ft.end(), std_list_s.begin(), std_list_s.end());

	comparison_print(ft_list_s, std_list_s, "Second list: ");
	comparison_print(ft_list_ft, std_list_ft, "Inserting elements of second list at the end: ");

	ft_list_ft.erase(++++++ft_list_ft.begin(), ------ft_list_ft.end());
	std_list_ft.erase(++++++std_list_ft.begin(), ------std_list_ft.end());

	comparison_print(ft_list_ft, std_list_ft, "Erased part of list: ");

	ft_list_ft.erase(++ft_list_ft.begin());
	std_list_ft.erase(++std_list_ft.begin());

	comparison_print(ft_list_ft, std_list_ft, "Erased element after begin: ");

	for (int i = 0; i < 10; ++i)
	{
		value = rand() % 100;
		ft_list_ft.push_back(value);
		std_list_ft.push_back(value);
	}

	comparison_print(ft_list_ft, std_list_ft, "Pushed 10 elements: ");

	for (int i = 0; i < 10; ++i)
	{
		ft_list_ft.pop_back();
		std_list_ft.pop_back();
	}

	comparison_print(ft_list_ft, std_list_ft, "Poped 10 elements: ");

	for (int i = 0; i < 10; ++i)
	{
		value = rand() % 100;
		ft_list_ft.push_front(value);
		std_list_ft.push_front(value);
	}

	comparison_print(ft_list_ft, std_list_ft, "Pushed front 10 elements: ");

	for (int i = 0; i < 10; ++i)
	{
		ft_list_ft.pop_front();
		std_list_ft.pop_front();
	}

	comparison_print(ft_list_ft, std_list_ft, "Popped front 10 elements: ");

	ft_list_ft.resize(ft_list_ft.size() + 3, 10);
	std_list_ft.resize(std_list_ft.size() + 3, 10);

	comparison_print(ft_list_ft, std_list_ft, "Resizing list with more elements: ");

	ft_list_ft.resize(6, 10);
	std_list_ft.resize(6, 10);

	comparison_print(ft_list_ft, std_list_ft, "Reducing list to first 6 elements: ");

	ft_list_s.resize(0, 10);
	std_list_s.resize(0, 10);

	comparison_print(ft_list_s, std_list_s, "Resizing other list to zero: ");

	comparison_print(ft_list_ft, std_list_ft, "First list: ");
	comparison_print(ft_list_f, std_list_f, "Second list: ");

	ft_list_ft.swap(ft_list_f);
	std_list_ft.swap(std_list_f);

	comparison_print(ft_list_ft, std_list_ft, "Swapped first list: ");
	comparison_print(ft_list_f, std_list_f, "Swapped second list: ");

	std::cout << std::endl;
	std::cout << YELLOW << "List operations: " << RESET << std::endl;

	ft_list_ft.sort(std::greater<int>());
	std_list_ft.sort(std::greater<int>());

	comparison_print(ft_list_ft, std_list_ft, "Sorted first list in descending order: ");

	ft_list_f.sort(std::greater<int>());
	std_list_f.sort(std::greater<int>());

	comparison_print(ft_list_f, std_list_f, "Sorted second list in descending order: ");

	ft_list_ft.sort();
	std_list_ft.sort();

	comparison_print(ft_list_ft, std_list_ft, "Sorted first list in ascending order: ");

	ft_list_f.sort();
	std_list_f.sort();

	comparison_print(ft_list_f, std_list_f, "Sorted second list in ascending order: ");

	ft_list_f.merge(ft_list_ft);
	std_list_f.merge(std_list_ft);

	comparison_print(ft_list_f, std_list_f, "Merg two sorted lists: ");

	for (int i = 0; i < 20; ++i)
	{
		value = rand() % 100;
		ft_list_s.push_back(value);
		std_list_s.push_back(value);
	}

	comparison_print(ft_list_s, std_list_s, "Pushing back 20 values to other list: ");

	ft_list_s.sort();
	std_list_s.sort();

	comparison_print(ft_list_s, std_list_s, "Sorted list: ");

	ft_list_s.merge(ft_list_f, std::greater<int>());
	std_list_s.merge(std_list_f, std::greater<int>());

	comparison_print(ft_list_s, std_list_s, "Merged with std::greater order: ");

	for (int i = 0; i < 20; ++i)
	{
		value = rand() % 100;
		ft_list_f.push_back(value);
		std_list_f.push_back(value);
	}

	comparison_print(ft_list_f, std_list_f, "Pushing back 20 values to other list: ");

	ft_list_s.splice(ft_list_s.begin(), ft_list_f, ft_list_f.begin());
	std_list_s.splice(std_list_s.begin(), std_list_f, std_list_f.begin());

	comparison_print(ft_list_s, std_list_s, "Transfer beginning of second list to beginning of first: ");
	comparison_print(ft_list_f, std_list_f, "Second list after transfer: ");

	ft_list_s.splice(ft_list_s.begin(), ft_list_f, ++++ft_list_f.begin(), ----ft_list_f.end());
	std_list_s.splice(std_list_s.begin(), std_list_f, ++++std_list_f.begin(), ----std_list_f.end());

	comparison_print(ft_list_s, std_list_s, "Transfer from third element to third from end "
										 "of second list to beginning of first:\n      ");
	comparison_print(ft_list_f, std_list_f, "Second list after transfer: ");

	ft_list_f.splice(ft_list_f.end(), ft_list_s);
	std_list_f.splice(std_list_f.end(), std_list_s);

	comparison_print(ft_list_f, std_list_f, "Transfer full first list to end of second:\n      ");
	comparison_print(ft_list_s, std_list_s, "First list: ");

	ft_list_f.insert(++ft_list_f.begin(), 10);
	ft_list_f.insert(++++++++++++ft_list_f.begin(), 10);
	ft_list_f.insert(--ft_list_f.end(), 10);
	std_list_f.insert(++std_list_f.begin(), 10);
	std_list_f.insert(++++++++++++std_list_f.begin(), 10);
	std_list_f.insert(--std_list_f.end(), 10);

	comparison_print(ft_list_f, std_list_f, "Inserting 3 elements of value 10 into list:\n      ");

	ft_list_f.remove(10);
	std_list_f.remove(10);

	comparison_print(ft_list_f, std_list_f, "Removing 3 elements of value 10:\n      ");

	ft_list_f.remove_if(unaryPredicate());
	std_list_f.remove_if(unaryPredicate());

	comparison_print(ft_list_f, std_list_f, "All even elements removed: ");

	ft_list_f.reverse();
	std_list_f.reverse();

	comparison_print(ft_list_f, std_list_f, "Reversed list: ");

	ft_list_f.sort();
	std_list_f.sort();

	comparison_print(ft_list_f, std_list_f, "Sorted: ");

	ft_list_f.unique();
	std_list_f.unique();

	comparison_print(ft_list_f, std_list_f, "Left only unique elements: ");

	ft_list_f.unique(binaryPredicate);
	std_list_f.unique(binaryPredicate);

	comparison_print(ft_list_f, std_list_f, "Left only elements that less than prev by 10 or more: ");

	std::cout << std::endl;
	std::cout << YELLOW << "Non-member overloads: " << RESET << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		ft_list_s.push_back(10);
		ft_list_t.push_back(10);
		std_list_s.push_back(10);
		std_list_t.push_back(10);
	}

	comparison_print(ft_list_t, std_list_t, "Pushed back 10 elements to two lists: ");
	comparison_print(ft_list_s, std_list_s, "Pushed back 10 elements to two lists: ");

	if (ft_list_t == ft_list_s)
		std::cout << RED << "      Lists are equal" << RESET << std::endl;
	if (std_list_t == std_list_s)
		std::cout << GREEN << "      Lists are equal" << RESET << std::endl;

	ft_list_t.push_back(9);
	std_list_t.push_back(9);

	comparison_print(ft_list_t, std_list_t, "Now pushing back 1 element to second list: ");

	if (ft_list_t >= ft_list_s)
		std::cout << RED << "      Second list is >= than first" << RESET << std::endl;
	if (std_list_t >= std_list_s)
		std::cout << GREEN << "      Second list is >= than first" << RESET << std::endl;
	if (ft_list_t > ft_list_s)
		std::cout << RED << "      Second list is > than first" << RESET << std::endl;
	if (std_list_t > std_list_s)
		std::cout << GREEN << "      Second list is > than first" << RESET << std::endl;
	if (ft_list_t != ft_list_s)
		std::cout << RED << "      Lists are not equal" << RESET << std::endl;
	if (std_list_t != std_list_s)
		std::cout << GREEN << "      Lists are not equal" << RESET << std::endl;

	ft_list_t.pop_back();
	ft_list_t.pop_back();
	std_list_t.pop_back();
	std_list_t.pop_back();

	comparison_print(ft_list_t, std_list_t, "Now popping back 2 elements from second list: ");

	if (ft_list_t < ft_list_s)
		std::cout << RED << "      Second list is < than first" << RESET << std::endl;
	if (std_list_t < std_list_s)
		std::cout << GREEN << "      Second list is < than first" << RESET << std::endl;
	if (ft_list_t <= ft_list_s)
		std::cout << RED << "      Second list is <= than first" << RESET << std::endl;
	if (std_list_t <= std_list_s)
		std::cout << GREEN << "      Second list is <= than first" << RESET << std::endl;

	comparison_print(ft_list_f, std_list_f, "First list: ");
	comparison_print(ft_list_s, std_list_s, "Second list: ");

	ft::swap(ft_list_f, ft_list_s);
	std::swap(std_list_f, std_list_s);

	comparison_print(ft_list_f, std_list_f, "First list: ");
	comparison_print(ft_list_s, std_list_s, "Second list: ");

	std::cout << std::endl;
	std::cout << BLUE << "///////////////////////END OF LIST TESTS///////////////////////" << RESET << std::endl;
	std::cout << std::endl;
}

void stack_tests()
{
	std::cout << BLUE << "///////////////////////STACK TESTS///////////////////////" << RESET << std::endl;
	std::cout << std::endl;

	ft::stack<char> ft_stack_f;
	std::stack<char> std_stack_f;

	ft::list<char> ft_list(10, 'a');
	ft::stack<char> ft_stack_s(ft_list);

	std::deque<char> std_list(10, 'a');
	std::stack<char> std_stack_s(std_list);

	char value;
	for (int i = 0; i < 10; ++i)
	{
		value = 'A' + rand() % ('z' - 'A');
		ft_stack_f.push(value);
		std_stack_f.push(value);
	}

	std::cout << RED << "      Cloned parent container, top element: " << ft_stack_s.top() << RESET << std::endl;
	std::cout << GREEN << "      Cloned parent container, top element: " << std_stack_s.top() << RESET << std::endl;

	std::cout << RED << "      Pushed back 10 values, top element is: " << ft_stack_f.top() << RESET << std::endl;
	std::cout << GREEN << "      Pushed back 10 values, top element is: " << std_stack_f.top() << RESET << std::endl;

	std::cout << RED << "      Size of container is: " << ft_stack_f.size() << RESET << std::endl;
	std::cout << GREEN << "      Size of container is: " << std_stack_f.size() << RESET << std::endl;

	ft::stack<char> ft_stack_th(ft_stack_f);
	std::stack<char> std_stack_th(std_stack_f);

	std::cout << RED << "      Copy constructor, top element is: " << ft_stack_th.top() << RESET << std::endl;
	std::cout << GREEN << "      Copy constructor, top element is: " << std_stack_th.top() << RESET << std::endl;

	ft_stack_th.pop();
	std_stack_th.pop();
	ft_stack_th.pop();
	std_stack_th.pop();

	std::cout << RED << "      Popping two elements, top element is: " << ft_stack_th.top() << RESET << std::endl;
	std::cout << GREEN << "      Popping two elements, top element is: " << std_stack_th.top() << RESET << std::endl;

	ft_stack_s = ft_stack_th;
	std_stack_s = std_stack_th;

	std::cout << RED << "      Assignation operator, top element is: " << ft_stack_s.top() << RESET << std::endl;
	std::cout << GREEN << "      Assignation operator, top element is: " << std_stack_s.top() << RESET << std::endl;

	std::cout << RED << "      Checking if container is empty: " << ft_stack_s.empty()
	<< "  Size: " << ft_stack_s.size() << RESET << std::endl;
	std::cout << GREEN << "      Checking if container is empty: " << std_stack_s.empty()
	<< "  Size: " << std_stack_s.size() << RESET << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		ft_stack_s.pop();
		std_stack_s.pop();
	}

	std::cout << RED << "      Popping 8 elements, checking if container is empty: " << ft_stack_s.empty()
	<< "  Size: "  << ft_stack_s.size() << RESET << std::endl;
	std::cout << GREEN << "      Popping 8 elements, checking if container is empty: " << std_stack_s.empty()
	<< "  Size: "  << std_stack_s.size() << RESET << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		ft_stack_f.pop();
		std_stack_f.pop();
	}

	for (int i = 0; i < 5; ++i)
	{
		ft_stack_s.push('a');
		std_stack_s.push('a');
		ft_stack_f.push('a');
		std_stack_f.push('a');
	}
	std::cout << RED << "      Clearing 2 stacks and pushing 5 equal elements to it, top is: " << ft_stack_s.top() << RESET << std::endl;
	std::cout << GREEN << "      Clearing 2 stacks and pushing 5 equal elements to it, top is: " << std_stack_s.top() << RESET << std::endl;

	if (ft_stack_s == ft_stack_f)
		std::cout << RED << "      Containers are equal" << RESET << std::endl;
	if (std_stack_s == std_stack_f)
		std::cout << GREEN << "      Containers are equal" << RESET << std::endl;

	ft_stack_s.pop();
	std_stack_s.pop();

	std::cout << RED << "      Now popping one element from second container" << RESET << std::endl;
	std::cout << GREEN << "      Now popping one element from second container" << RESET << std::endl;

	if (ft_stack_f > ft_stack_s)
		std::cout << RED << "      First stack is > than second" << RESET << std::endl;
	if (std_stack_f > std_stack_s)
		std::cout << GREEN << "      First stack is > than second" << RESET << std::endl;
	if (ft_stack_f >= ft_stack_s)
		std::cout << RED << "      First stack is >= than second" << RESET << std::endl;
	if (std_stack_f >= std_stack_s)
		std::cout << GREEN << "      First stack is >= than second" << RESET << std::endl;

	ft_stack_f.pop();
	std_stack_f.pop();
	ft_stack_f.pop();
	std_stack_f.pop();

	std::cout << RED << "      Now popping 2 elements from first container" << RESET << std::endl;
	std::cout << GREEN << "      Now popping 2 elements from first container" << RESET << std::endl;

	if (ft_stack_f < ft_stack_s)
		std::cout << RED << "      First container is < than second" << RESET << std::endl;
	if (std_stack_f < std_stack_s)
		std::cout << GREEN << "      First container is < than second" << RESET << std::endl;
	if (ft_stack_f <= ft_stack_s)
		std::cout << RED << "      First container is <= than second" << RESET << std::endl;
	if (std_stack_f <= std_stack_s)
		std::cout << GREEN << "      First container is <= than second" << RESET << std::endl;
	if (ft_stack_f != ft_stack_s)
		std::cout << RED << "      Stacks are not equal" << RESET << std::endl;
	if (std_stack_f != std_stack_s)
		std::cout << GREEN << "      Stacks are not equal" << RESET << std::endl;

	std::cout << std::endl;
	std::cout << BLUE << "///////////////////////END OF STACK TESTS///////////////////////" << RESET << std::endl;
	std::cout << std::endl;
}

void queue_tests()
{
	std::cout << BLUE << "///////////////////////QUEUE TESTS///////////////////////" << RESET << std::endl;
	std::cout << std::endl;

	ft::queue<char> ft_queue_f;
	std::queue<char> std_queue_f;

	ft::list<char> ft_list(10, 'a');
	ft::queue<char> ft_queue_s(ft_list);

	std::deque<char> std_list(10, 'a');
	std::queue<char> std_queue_s(std_list);

	char value;
	for (int i = 0; i < 10; ++i)
	{
		value = 'A' + rand() % ('z' - 'A');
		ft_queue_f.push(value);
		std_queue_f.push(value);
	}

	std::cout << RED << "      Cloned parent container, front element: " << ft_queue_f.front() << RESET << std::endl;
	std::cout << GREEN << "      Cloned parent container, front element: " << std_queue_s.front() << RESET << std::endl;

	std::cout << RED << "      Pushed back 10 values, front element is: " << ft_queue_f.front() << RESET << std::endl;
	std::cout << GREEN << "      Pushed back 10 values, front element is: " << std_queue_f.front() << RESET << std::endl;

	std::cout << RED << "      Back element is: " << ft_queue_f.back() << RESET << std::endl;
	std::cout << GREEN << "      Back element is: " << std_queue_f.back() << RESET << std::endl;

	std::cout << RED << "      Size of container is: " << ft_queue_f.size() << RESET << std::endl;
	std::cout << GREEN << "      Size of container is: " << std_queue_f.size() << RESET << std::endl;

	ft::queue<char> ft_queue_th(ft_queue_f);
	std::queue<char> std_queue_th(std_queue_f);

	std::cout << RED << "      Copy constructor, front element is: " << ft_queue_th.front() << RESET << std::endl;
	std::cout << GREEN << "      Copy constructor, front element is: " << std_queue_th.front() << RESET << std::endl;

	ft_queue_th.pop();
	std_queue_th.pop();
	ft_queue_th.pop();
	std_queue_th.pop();

	std::cout << RED << "      Popping two elements, front element is: " << ft_queue_th.front() << RESET << std::endl;
	std::cout << GREEN << "      Popping two elements, front element is: " << std_queue_th.front() << RESET << std::endl;

	ft_queue_s = ft_queue_th;
	std_queue_s = std_queue_th;

	std::cout << RED << "      Assignation operator, front element is: " << ft_queue_s.front() << RESET << std::endl;
	std::cout << GREEN << "      Assignation operator, front element is: " << std_queue_s.front() << RESET << std::endl;

	std::cout << RED << "      Checking if container is empty: " << ft_queue_s.empty()
			  << "  Size: " << ft_queue_s.size() << RESET << std::endl;
	std::cout << GREEN << "      Checking if container is empty: " << std_queue_s.empty()
			  << "  Size: " << std_queue_s.size() << RESET << std::endl;

	for (int i = 0; i < 8; ++i)
	{
		ft_queue_s.pop();
		std_queue_s.pop();
	}

	std::cout << RED << "      Popping 8 elements, checking if container is empty: " << ft_queue_s.empty()
			  << "  Size: "  << ft_queue_s.size() << RESET << std::endl;
	std::cout << GREEN << "      Popping 8 elements, checking if container is empty: " << std_queue_s.empty()
			  << "  Size: "  << std_queue_s.size() << RESET << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		ft_queue_f.pop();
		std_queue_f.pop();
	}

	for (int i = 0; i < 5; ++i)
	{
		ft_queue_s.push('a');
		std_queue_s.push('a');
		ft_queue_f.push('a');
		std_queue_f.push('a');
	}
	std::cout << RED << "      Clearing 2 queues and pushing 5 equal elements to it, back is: " << ft_queue_s.back() << RESET << std::endl;
	std::cout << GREEN << "      Clearing 2 queues and pushing 5 equal elements to it, front is: " << std_queue_s.back() << RESET << std::endl;

	if (ft_queue_s == ft_queue_f)
		std::cout << RED << "      Containers are equal" << RESET << std::endl;
	if (std_queue_s == std_queue_f)
		std::cout << GREEN << "      Containers are equal" << RESET << std::endl;

	ft_queue_s.pop();
	std_queue_s.pop();

	std::cout << RED << "      Now popping one element from second container" << RESET << std::endl;
	std::cout << GREEN << "      Now popping one element from second container" << RESET << std::endl;

	if (ft_queue_f > ft_queue_s)
		std::cout << RED << "      First queue is > than second" << RESET << std::endl;
	if (std_queue_f > std_queue_s)
		std::cout << GREEN << "      First queue is > than second" << RESET << std::endl;
	if (ft_queue_f >= ft_queue_s)
		std::cout << RED << "      First queue is >= than second" << RESET << std::endl;
	if (std_queue_f >= std_queue_s)
		std::cout << GREEN << "      First queue is >= than second" << RESET << std::endl;

	ft_queue_f.pop();
	std_queue_f.pop();
	ft_queue_f.pop();
	std_queue_f.pop();

	std::cout << RED << "      Now popping 2 elements from first container" << RESET << std::endl;
	std::cout << GREEN << "      Now popping 2 elements from first container" << RESET << std::endl;

	if (ft_queue_f < ft_queue_s)
		std::cout << RED << "      First container is < than second" << RESET << std::endl;
	if (std_queue_f < std_queue_s)
		std::cout << GREEN << "      First container is < than second" << RESET << std::endl;
	if (ft_queue_f <= ft_queue_s)
		std::cout << RED << "      First container is <= than second" << RESET << std::endl;
	if (std_queue_f <= std_queue_s)
		std::cout << GREEN << "      First container is <= than second" << RESET << std::endl;
	if (ft_queue_f != ft_queue_s)
		std::cout << RED << "      Queues are not equal" << RESET << std::endl;
	if (std_queue_f != std_queue_s)
		std::cout << GREEN << "      Queues are not equal" << RESET << std::endl;

	std::cout << std::endl;
	std::cout << BLUE << "///////////////////////END OF QUEUE TESTS///////////////////////" << RESET << std::endl;
	std::cout << std::endl;
}

int main()
{
	srand(time(NULL));

	list_tests();
	stack_tests();
	queue_tests();
}

//
//#include <sys/time.h>
//
//int main()
//{
//	srand(time(NULL));
//
//	ft::list<int> sorto;
//	ft::vector<int> vec;
//	std::list<int> sort_d;
////	int value;
//	size_t i = 0;
//
////	while (i < 1000000)
////	{
////		std::cout << "p" << std::endl;
////		++i;
////	}
////	i = 0;
//
//
//	std::cout << "st" << std::endl;
////	while (i < 10000)
////	{
//////		value = rand() % 100;
//////		std::cout << "E" << std::endl;
////		sort.push_back(1);
//////		std::cout << "G" << std::endl;
//////		sort_d.push_back(value);
////		++i;
////	}
//
//
//	i = 0;
//	int j = 1;
//	while (j < 2)
//	{
//		i = 0;
//		while (i < 2000000)
//		{
//	//		sorto.push_back( rand() % 10000);
//			sort_d.push_back(1);
//			++i;
//		}
//		++j;
//	}
//
//	std::cout << "lol" << std::endl;
//////	struct timeval tv_start;
//////	struct timeval tv_end;
////
//////	gettimeofday(&tv_start, NULL);
////
//	sort_d.sort();
////
////
//////	gettimeofday(&tv_end, NULL);
//	print(sort_d.begin(), sort_d.end(), "Sort: ", FT);
//////	long long usecs = tv_end.tv_usec - tv_start.tv_usec;
////
//////	std::cout << RED << "Sec: " <<   ((tv_end.tv_sec - tv_start.tv_sec) * 10000) + (double )(tv_end.tv_usec - tv_start.tv_usec)/100 << "           Usec: " << usecs << RESET << std::endl;
////
////	gettimeofday(&tv_start, NULL);
////
////	sort_d.sort();
////
////	gettimeofday(&tv_end, NULL);
////
////	long long usecs_def = tv_end.tv_usec - tv_start.tv_usec;
////
//////	std::cout << GREEN << "Sec: " << tv_end.tv_sec - tv_start.tv_sec << "           Usec: " << usecs_def << RESET << std::endl;
////
//////	std::cout << "Percentage: " << usecs_def / usecs * 100 << std::endl;
//
//
//}