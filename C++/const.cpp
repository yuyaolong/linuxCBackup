#include <iostream>

void func(int* &ptr) {
	ptr = new int;
}

int main(int argc, char const *argv[])
{
	int v = 1;
	int *a = &v;
	func(a);
	const int &b = v;
	int const &c = v;
	return 0;
}

