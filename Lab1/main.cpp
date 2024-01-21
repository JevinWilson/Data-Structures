#include "array_list.h"
#include "array_list_class.cpp"

int main()
{
	ssuds::ArrayList tester;
	tester.append("Bob");
	tester.append("Carl");
	std::cout << tester.size() << std::endl;	// 2
	std::cout << tester.get(0) << std::endl;	// Bob
	std::cout << tester.get(1) << std::endl;	// Carl
	std::cout << "size of tester = " << tester.size() << "\n";	// 2
	
	return 0;
}