#include <iostream>

class A
{
public:
	A(int val)
	{
		this->val = val;
	}

	void open()
	{
		std::cout << "open\n";
	}

	void close()
	{
		std::cout << "close\n";
	}
	int val;
};

class B
{
public:
	B(int val):a {new A(val)}
	{
		a->open();
	}

	//the default implementation performs shallow copy; and we require a deep copy
	B(const B &b)
	{
		std::cout << "copy constructor\n";
		this->a = new A(3);
	}

	//The Copy-Swap Idiom, which provides an efficient, safe way to implement 
	//the assignment operator by reusing the copy constructor code.
	//When the assignment operator is called, the first thing that happens is a 
	//copy of the right-hand-side is made. Should the copy constructor throw an 
	//exception this will happen before the call to operator= (which will never get called); 
	//thus leaving the left-hand-side object unaffected.
	//pass by value to reuse copy constructor
	B& operator=(B b)
    {
    	//instead of B &b; B tmp(b);
        std::cout << "assignment operator\n";
        swap(b);
        
        return *this;
    }

    //class must also implement a swap() function to perform a member-by-member swap
    void swap(B &b)
	{
		std::swap(this->a, b.a);
	}

	void print()
	{
		std::cout << "i got " << a->val << "\n";
	}

	~B()
	{
		std::cout << a->val << " ";
		a->close();
		delete a;
	}
private:
	A *a;
};

B test_Named_Return_Value()
{
	//the compiler can optimise this and construct the return object directly 
	//into the caller’s object. In this case a ‘normal’ constructor is called 
	//rather than a copy constructor. 
	return B(99);
}


int main()
{
	B b = test_Named_Return_Value();
	B c(88);
	c = b;//after assigned c is destroyed
	b.print();
	c.print();
	//variable push to stack => b is destroyed last
	return 0;
}

/*

The Rule of the Big Three states that if you have implemented either
	A destructor
	An assignment operator
	A copy constructor
=> You should also implement the other two.

*/
