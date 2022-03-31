#include <iostream>

int func(int a, int b)
{
	return a*b;
}

void byRef(int &i)
{
	std::cout << "int &i\n";
}

void byRef(const int &i)
{
	std::cout << "const int &i\n";
}

void byRef(int &&i)
{
	std::cout << "int &&i\n";
}

void byRef(const int &&i)
{
	std::cout << "const int &&i\n";
}


int main()
{
	int &&r = func(2, 3);
	byRef(r);
	byRef(func(2, 3));
	//for constant r-values it always prefers constant l-value 
	//references (for backward compatibility). This means 
	//overloading functions for const T&& has no real application.
	byRef(17);
	return 0;
}
