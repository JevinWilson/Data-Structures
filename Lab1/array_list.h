#include <string>

namespace ssuds
{
	class ArrayList
	{
	protected:
		std::string* mData;		// Holds the current DYNAMIC ARRAY of strings
		unsigned int mSize;
	public:
		ArrayList();
		~ArrayList();     // Destructor
		void append(std::string s);
		// ... and the rest of the methods

		unsigned int size();
		void insert(std:: string value, unsigned int index);
		void clear();
		std::string get(unsigned int index);
		int find(std::string value, int startIndex);
		void remove(unsigned int index);
		int remove_all(std::string value);
	};
}
