

#ifndef CONTAINERS_QUEUE_HPP
#define CONTAINERS_QUEUE_HPP


namespace ft {

	template< class T, class Container = ft::list<T> >
	class queue {

	protected:
		Container C;
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		explicit queue( const Container& cont = Container() ) : C(cont) {}
		queue( const queue& other ) : C(other.C) {}
		~queue() {}

		queue& operator=( const queue& other ) { C = other.C; return (*this); }
		reference front() { return (C.front()); }
		const_reference front() const { return (C.front()); }
		reference back() { return (C.back()); }
		const_reference back() const { return (C.back()); }
		bool empty() const { return (C.empty()); }
		size_type size() const { return (C.size()); }
		void push( const value_type& value ) { C.push_back(value); }
		void pop() { C.pop_front(); }
		friend bool operator==( const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs )
		{ return (lhs.C == rhs.C); }
		friend bool operator!=( const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs )
		{ return (lhs.C != rhs.C); }
		friend bool operator<( const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs )
		{ return (lhs.C < rhs.C); }
		friend bool operator<=( const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs )
		{ return (lhs.C <= rhs.C); }
		friend bool operator>( const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs )
		{ return (lhs.C > rhs.C); }
		friend bool operator>=( const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs )
		{ return (lhs.C >= rhs.C); }
	};
}

#endif
