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

	// create a temp array one element bigger
	std::string* newArray = new std::string[mSize + 1];
	// copy the elements from the old array to the new
	for (int i = 0; i < mSize; i++) {
		newArray[i] = mData[i];
	}
	// add new element
	newArray[mSize] = s;
	// free up the old array
	delete[] mData;
	// update variables
	mData = newArray;
	mSize++;
}

ssuds::ArrayList::~ArrayList() 
{
	// Free up the memory used by the array.
	// We need to free up the array itself, and the string objects in it.
	// We need to set mSize to 0.
	// We need to set mData to NULL.
	if (mData!= nullptr) {
		delete[] mData;
		mData = nullptr;
	}
	mSize = 0;
}

void ssuds::ArrayList::insert(std::string value, unsigned int index) {
	// check if index is in range
	if (index > mSize) {
		throw std::out_of_range("Index out of range");
	}
	// allocate new array
	std::string* newArray = new std::string[mSize + 1];
	// copy elements up to index
	for (int i = 0; i < index; i++) {
		newArray[i] = mData[i];
	}
	// add new element
	newArray[index] = value;
	// copy remaining elements
	for (int i = index; i < mSize; i++) {
		newArray[i + 1] = mData[i];
	}
	// free up old array
	delete[] mData;
	// update instance variables
	mData = newArray;
	mSize++;
}

void ssuds::ArrayList::clear() {
	// delete existing array
	if (mData!= nullptr) {
		delete[] mData;
		mData = nullptr;
	}
	// reset size
	mSize = 0;
}

std::string ssuds::ArrayList::get(unsigned int index) {
	// check if its between bound
	if (index >= mSize) {
		throw std::out_of_range("Index out of range");
	}
	return mData[index];
}

int ssuds::ArrayList::find(std::string value, int startIndex) {
	// check if index is in range
	for (int i = startIndex; i < mSize; i++) {
		// if we find the value, return its index
		if (mData[i] == value) {
			return i;
		}
	}
	return -1;
}

void ssuds::ArrayList::remove(unsigned int index) {
	// check if index is in range
	if (index >= mSize) {
		throw std::out_of_range("Index out of range");
	}
	// create new array
	std:: string* newArray = new std::string[mSize - 1];
	// copy elements before index
	for (int i = 0; i < index; i++) {
		newArray[i] = mData[i];
	}
	// copy elements after index
	for (int i = index + 1; i < mSize; i++) {
		newArray[i - 1] = mData[i];
	}
	// delete old array
	delete[] mData;
	// update instance variables
	mData = newArray;
	mSize--;
}

int ssuds::ArrayList::remove_all(std::string value) {
	int count = 0;
	// search for value and remove each occurrence
	int index = find(value, 0);
	while (index != -1) {
		// remove found element
		remove(index);
		count++;
		// find next occurrence of value
		index = find(value, index);
	}
	return count;
}

// Define the other method bodies here...