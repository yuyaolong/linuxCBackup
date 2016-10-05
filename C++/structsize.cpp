#include <iostream>

struct X
{
	int a;
	char b;
	int c;

	virtual void set_value(int v) { a = v; }
	virtual int get_value() { return a; }
	virtual void increase_value() { a++; }
};

int main(int argc, char const *argv[])
{
	std::cout << sizeof(X) << std::endl;
	return 0;
}