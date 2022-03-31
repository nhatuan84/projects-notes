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
	//if you cannot define a default constructor for the class it cannot support move semantics.
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

	//Copying objects may not be the best solution in many situations. 
	//It can be very expensive in terms of creating, copying and then destroying temporary objects.
	//It would be nicer if we could just ‘take ownership’ of the temporary’s resources, 
	//freeing it of the burden of de-allocating the resource, and freeing us of the burden of 
	//re-allocating. This is concept is known as ‘resource pilfering’.
	B& operator=(B &b)
    {
    	B tmp(b);
    	//instead of B &b; B tmp(b);
        std::cout << "assignment operator\n";
        swap(tmp);
        
        return *this;
    }

    //class must also implement a swap() function to perform a member-by-member swap
    void swap(B &b)
	{
		std::swap(this->a, b.a);
	}

	//Parameter for the move constructor is not const – we need to modify the parameter.
	//When the r-value object goes out of scope its destructor will do nothing.
	//The move constructor is qualified as noexcept, the move constructor will not throw an exception
	//=> If the move constructor may throw an exception the container will normally copy the object rather than move it
	//without a move constructor to bind to, the compiler preferred the next best 
	//thing – binding the r-value object to a const B&; that is, the copy constructor)
	B(B &&b) noexcept
	:B(8)
	{
		std::cout << "move constructor\n";
		//this->a = b.a;
		//leaving the object in 'empty' state that its destructor will not fail or throw an exception.
		//b.a = nullptr;
		//reuse swap idiom
		swap(b);
	}

	B& operator=(B &&b)
    {
    	//instead of B &b; B tmp(b);
        std::cout << "move assignment\n";
        //collapse rules:
        //A& & becomes A&
		//A& && becomes A&
		//A&& & becomes A&
		//A&& && becomes A&&
        swap(b);
        
        return *this;
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

B test()
{
	return B(99);
}

//need -fno-elide-constructors to disable compiler optimization
//std::move here doesn’t actually do any moving; it just converts an l-value into an r-value. 
//This forces the compiler to use the object’s move constructor (if defined) rather than the copy constructor.
int main()
{
	//B b = test();
	B b(1);
	B c(2);
	c = std::move(b);
	return 0;
}

/*

“The Rule of The Big Four (and a half)” says if you’ve written one of the above functions then you must have a policy about the others. It doesn’t say you have to write them. In fact, you have to have a resource management policy for every class you create. Your policy can be one of the following:

Use the compiler-provided versions of these functions. In other words, you’re not doing any resource management in the class.
Write your own copy functions to perform deep copy, but don’t provide move semantics.
Write your own move functions, but don’t support copying.
Disable copying and move semantics for the class, because it doesn’t make sense to allow it.
Suppressing move and copy is straightforward; and there are two ways to do it:

Make the appropriate function declarations private. (C++98-style)
Use the =delete notation

*/
