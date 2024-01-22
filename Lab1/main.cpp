#include "array_list.h"
#include <fstream>

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
	

	//not done :(
	/*std::ifstream inFile("input.txt");
	std::string line;

	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			tester.append(line);
		}
		inFile.close();
	}
	else {
		std::cerr << "Error opening file\n";
	}

	bool running = true;
	int choice;
	std::string value;

	while (running) {
		std::cout << "Enter a choice:\n";
		std::cout << "1. Append\n";
		std::cout << "2. Size\n";
		std::cout << "3. Insert\n";
		std::cout << "4. Clear\n";
		std::cout << "5. Get\n";
		std::cout << "6. Find\n";
		std::cout << "7. Remove\n";
		std::cout << "8. Remove All\n";
		std::cout << "9. Exit\n";
		std::cin >> choice;

		switch (running) {
			case 1:
			// Append
			std:: string value;
			std::cout << "Enter a string to append: ";
			std::cin >> value;
			tester.append(value);
			break;

			case 2:
			// Size
			std::cout << "Size = " << tester.size() << std::endl;
			break;

			case 3:
			// Insert
			std::string value;
			unsigned int index;
			std::cout << "Enter strig to insert: ";
			std::cin >> value;

			std::cout << "Enter index to insert at: ";
			std::cin >> index;
			tester.insert(value, index);
			break;

			case 4:
			// Clear
			tester.clear();
			std::cout << "list cleared\n";
			break;

			case 5:
			// Get
			unsigned int index;
			std::cout << "Enter index to get: ";
			std::cin >> index;
			break;

			case 6:
			// Find
			std::string value;
			std::cout << "Enter string to find: ";
			std::cin >> value;

			if (tester.find(value, 0) == -1) {
				std::cout << "Not found\n";
			}
			else {
				std::cout << "Found at index " << tester.find(value, 0) << std::endl;
			
		}
	}

	return 0;*/
	
}