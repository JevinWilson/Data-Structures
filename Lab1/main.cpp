#include "array_list.h"
//#include "array_list_class.cpp"

int main()
{
	ssuds::ArrayList tester;
	tester.append("Bob");
	tester.append("Carl");
	tester.append("John");
	tester.append("Parker");
	tester.append("Something");
	tester.append("Something");
	tester.append("Jevin");
	tester.insert("Insert", 1);
	tester.remove(1);
	std::cout << "sizer before clear = " << tester.size() << std::endl;	// 3
	std::cout << tester.get(0) << std::endl;	// Bob
	std::cout << tester.get(1) << std::endl;	// Insert
	std::cout << tester.get(2) << std::endl;	// Carl
	std::cout << tester.get(3) << std::endl;	// John
	std::cout << tester.get(4) << std::endl;	// Parker
	std::cout << tester.get(5) << std::endl;	// Something
	std::cout << tester.get(6) << std::endl;	// Something
	std::cout << tester.get(7) << std::endl;	// Jevin

	// get
	try {
		unsigned int index = 7;
		std::string element = tester.get(index);
		std::cout << "element at index " << index << " = " << element << std::endl; // Jevin
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	tester.clear();
	std::cout << "size after clear = " << tester.size() << "\n";	// 0
	
	
	
	return 0;
}