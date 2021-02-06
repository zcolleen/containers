

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP

namespace ft {

	template< class T, class Container = ft::list<T> >
	class stack {

	protected:
		Container C;
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		explicit stack( const Container& cont = Container() ) : C(cont) {}
		stack( const stack& other ) : C(other.C) {}
		~stack() {}

		stack& operator=( const stack& other ) { C = other.C; return (*this); }
		reference top() { return (C.back()); }
		const_reference top() const { return (C.back()); }
		bool empty() const { return (C.empty()); }
		size_type size() const { return (C.size()); }
		void push( const value_type& value ) { C.push_back(value); }
		void pop() { C.pop_back(); }
		friend bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{ return (lhs.C == rhs.C); }
		friend bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{ return (lhs.C != rhs.C); }
		friend bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{ return (lhs.C < rhs.C); }
		friend bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{ return (lhs.C <= rhs.C); }
		friend bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{ return (lhs.C > rhs.C); }
		friend bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{ return (lhs.C >= rhs.C); }
	};
}


#endif
