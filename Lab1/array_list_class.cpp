#include <iostream>
#include "array_list.h"

ssuds::ArrayList::ArrayList()
{
	mSize = 0;
	mData = nullptr;		// Just like NULL, but only assignable to pointers
}

unsigned int ssuds::ArrayList::size()
{
	return mSize;
}

void ssuds::ArrayList::append(std::string s)
{
	// Two possibilities: 
	// 1: we have an empty list
	//     we need to allocate the array to be of size 1
	//     we need to assign s to the only spot in the array
	//     we need to set mSize to 1.
	// 2: we have a list with stuff in it
	//     we need to allocate a temporary array that's one bigger than our current
	//         one.
	//     we need to copy all the elements from the old array to the new
	//     we need to add s to the last spot in that temporary array
	//     we need to free up the old array
	//     we need to make the larger array THE array.
	//     we will add one to mSize
}

ssuds::ArrayList::~ArrayList() 
{
	// Free up the memory used by the array.
	// We need to free up the array itself, and the string objects in it.
	// We need to set mSize to 0.
	// We need to set mData to NULL.
	if (array != nullptr) // free the array
	{	
		delete[] array;
		array = nullptr;
	}

	for (int i = 0; i < length; i++) 
	{
		if (array[i]!= nullptr) // free the strings in the array
		{	
		delete array[i];
		array[i] = nullptr;
		}
	}
	length = 0;
}

// Define the other method bodies here...