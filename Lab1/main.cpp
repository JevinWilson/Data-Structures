#include "array_list.h"
//#include "array_list_class.cpp"

int main()
{
	ssuds::ArrayList tester;
	tester.append("Bob");
	tester.append("Carl");
	tester.append("Something");
	tester.append("Parker");
	tester.append("John");
	tester.append("Something");
	tester.append("Jevin");
	
	tester.insert("Insert", 1);
	
	tester.remove(1);
	
	int find = tester.find("Jevin", 0);
	
	int remove_all = tester.remove_all("Something");
	
	std::cout << "size before clear = " << tester.size() << std::endl;	// 3
	std::cout << tester.get(0) << std::endl;	// Bob
	//std::cout << tester.get(1) << std::endl;	// Insert
	std::cout << tester.get(1) << std::endl;	// Carl
	//std::cout << tester.get(2) << std::endl;	// Something
	std::cout << tester.get(2) << std::endl;	// Parker
	std::cout << tester.get(3) << std::endl;	// John
	//std::cout << tester.get(5) << std::endl;	// Something
	std::cout << tester.get(4) << std::endl;	// Jevin

	// get
	try {
		unsigned int index = 3;
		std::string element = tester.get(index);
		std::cout << "element at index " << index << " = " << element << std::endl; // Parker
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "Jevin was found at index " << find << std::endl;	// 6

	tester.clear();
	std::cout << "size after clear = " << tester.size() << "\n";	// 0
	
	return 0;
}