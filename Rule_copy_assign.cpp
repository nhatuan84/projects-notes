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
	B& operator=(const B& b)
    {
        std::cout << "assignment operator\n";
        this->a = new A(1);
        return *this;
    }
	void print()
	{
		std::cout << a->val << "\n";
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

//disable NRV by g++ -o test object_props1.cpp -fno-elide-constructors
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
	c = b;
	c.print();
	//variable push to stack => b is destroyed last
	return 0;
}
