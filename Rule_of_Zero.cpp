#include <iostream>
#include <memory>
#include <vector>


/*
Use a std::unique_ptr if your class can be moved, but should not be copied:
*/
class A
{
public:
	A(int x)
	:val{std::make_unique<int>(x)}
	{
	}

	void print()
	{
		std::cout << *val.get() << "\n";
	}

private:
	std::unique_ptr<int> val;
};

/*

Use a shared_ptr if you need to support copying as well as moving

*/

class B
{
public:
	B(int x)
	:val{std::make_shared<int>(x)}
	{
	}

	void print()
	{
		std::cout << *val.get() << "\n";
	}

private:
	std::shared_ptr<int> val;
};

/*
This code works because the compiler generates default implementations of the copy constructor, 
move constructor and assignment operators for your class. These default implementations will 
invoke the appropriate functions on the shared_ptr / unique_ptr (if available). 
The C++ Standard limits when these constructors are created, as follows:
*/

/*
Notice 
std::string supports both copying and move semantics; and after move leaves 
the string object as ‘empty’ (in this case, the null string).

When a std::array is moved it calls the move assignment operator on each of its 
elements (as with all other objects, if the element in the array doesn’t support move it is copied instead)

*/
int main()
{
	A a(9);
	std::vector<A> v;
	v.emplace_back(A(8)); //=> ok to move rvalue
	//v.emplace_back(a); => not allow copy
	v[0].print();
	//v[1].print();

	std::vector<B> vv;
	B b(5);
	vv.emplace_back(b);
	vv.emplace_back(B(6));
	vv[0].print();
	vv[1].print();
	return 0;
}

/*

The Rule of Zero
An alternative to “The Rule of The Big Four (and a half)” has appeared in the form of “The Rule of Zero”. 
“The Rule of Zero” basically states:

You should NEVER implement a destructor, copy constructor, move constructor or assignment operators in your code.

With the (very important) corollary to this:

You should NEVER use a raw pointer to manage a resource.

The aim of The Rule of Zero is to simplify your application code by deferring all resource 
management to Standard Library constructs, and letting them do all the hard work for you.

The Rule of Zero and dynamic memory
If your code must dynamically create objects prefer to use std::unique_ptr or std::shared_ptr. 

The Rule of Zero’s corollary still applies when it comes to arrays: don’t use them. 
This becomes particularly relevant when the arrays are created dynamically (with new).

The Rule of Zero prefers that we use Standard Library container classes (vector, list, ...)

*/
