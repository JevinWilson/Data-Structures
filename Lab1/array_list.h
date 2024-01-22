#ifndef ARRAY_LIST_CLASS_H
#define ARRAY_LIST_CLASS_H

#include <iostream>
#include <string>

namespace ssuds
{
	/// @brief ArrayList class
	class ArrayList
	{
	protected:
		std::string* mData;		// Holds the current DYNAMIC ARRAY of strings
		unsigned int mSize;
	public:
		/// @brief Constructor for the ArrayList class
		/// Creates an empty ArrayList
		ArrayList();

		/// @brief of the ArrayList class
		/// Deletes the deletes array of strings
		~ArrayList();

		/// @brief a string to the end of the ArrayList
		/// @param s is a string to be appended 
		void append(std::string s);

		/// @brief gets the size of the ArrayList
		/// @return size of the ArrayList
		unsigned int size();

		/// @brief insert a element into the ArrayList at a given index
		/// @param value element being inserted
		/// @param index position inserted at
		void insert(std:: string value, unsigned int index);

		/// @brief clears the ArrayList
		void clear();

		/// @brief gets element at said index
		/// @param index position of said element
		/// @return element at said index
		std::string get(unsigned int index);

		/// @brief find element in the ArrayList
		/// @param value element to find
		/// @param startIndex start index to search from
		/// @return element index if found, -1 if not found
		int find(std::string value, int startIndex);

		/// @brief remove element at said index
		/// @param index position of said element to remove
		void remove(unsigned int index);

		/// @brief remove all elements with said value
		/// @param value element to remove
		/// @return number of elements removed
		int remove_all(std::string value);
	};
}
#endif