#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char const *argv[])
{
	string s1 = "a b c d";
	string s2 = "a\nb\nc\nd";
	stringstream ss1(s1), ss2(s2);

	string tok;
	
	for (int i = 0; i < 6; ++i)
	{
		
		cout << !(ss2 >> tok) << endl;
		
	}
	

	return 0;
}