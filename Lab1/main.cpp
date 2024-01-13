#include "array_list.h"
#include "array_list_class.cpp"

int main()
{
	ssuds::ArrayList tester;
	tester.append("Bob");
	tester.append("Carl");
	std::cout << "size of tester = " << tester.size() << "\n";	// 2
	
	return 0;
}