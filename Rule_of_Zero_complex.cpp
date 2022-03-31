#include <iostream>
#include <memory>
#include <list>


class A
{
public:
	A(int x)
	:m_a{std::make_unique<int>(x)}
	{
	}

	void print()
	{
		std::cout << *m_a.get() << "\n";
	}

private:
	std::unique_ptr<int> m_a;
};


class B
{
public:
	B(int x)
	:m_b {std::make_unique<A>(x)}
	{
	}

	void print() const
	{
		m_b.get()->print();
	}

private:
	std::unique_ptr<A> m_b;
};

class C
{
public:
	C(){}
	C(int x)
	{
		for(int i=0; i<x; i++)
		{
			l.emplace_back(B(i+1));
		}
	}
	void print()
	{
		for (auto it = l.cbegin(); it != l.cend(); ++it)
    	{
    		it->print();
    	}
	}

private:
	std::list<B> l;
};

int main()
{
	C a(9);
	C b;
	b = std::move(a);
	b.print();
	return 0;
}


