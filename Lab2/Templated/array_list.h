// #pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <sstream>

namespace ssuds
{
	template <class T>

	/// An ArrayList is an array-based data structure. 
	class ArrayList
	{
	protected:
		/// The current size of mData (in elements, not bytes)
		int mSize;

		/// @brief The current capacity of mData (in elements, not bytes)
		int mCapacity;

		/// The array of data we're currently holding
		T* mData;

	public:
		/// Default constructor
		ArrayList() : mSize(0), mCapacity(0), mData(nullptr) {}

		/// Destructor
		~ArrayList() {
			if (mData)
				delete[] mData;
		}

		/// <summary>
		///  Inserts a new element at the end of the array
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(T val);

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear();

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(T val, int start_index = 0) const;

		/// <summary>
		/// Gets the data item at the given index.  This will throw an std::out_of_bounds exception if index is invalid (less than 0 or >= size)
		/// </summary>
		/// <param name="index">the index of the thing to return</param>
		/// <returns>the value at the given index</returns>
		T get(int index) const;

		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(T val, int index);

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <returns>the data item that was just removed</returns>
		T remove(int index);

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(T val);

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		int size() const;

		/// capacity getter
		int capacity() const {
			return mCapacity;
		}
		
		/// get method with []
		const T &operator[](int index) const {
			if (index < 0 || index >= mSize) {
				throw std::out_of_range("Index out of range");
			}
			return mData[index];
		}

		/// friend function for stream operator
		friend std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list) {
			// indicate the start of the list
			os << "[";
			// loop through ArrayList
			for (int i = 0; i < list.mSize; ++i) {
				// inside the loop each element is inserted to output stream
				os << list.mData[i];
				// if this is not the last element, insert a comma
				if (i < list.mSize - 1) {
					os << ", ";
				}
			}
			// indicate the end of the list
			os << "]";
			return os;
		}

		/// overload the "=" operator
		// copy constructor
		ArrayList(const ArrayList<T>& other): mSize(other.mSize), mCapacity(other.mCapacity), mData(nullptr) {
			if (other.mData) {
				mData = new T[mCapacity];
				for (int i = 0; i < mSize; i++) {
					mData[i] = other.mData[i];
				}
			}
		}
		// assignment operator
		ArrayList<T>& operator=(const ArrayList<T>& other) {
			delete[] mData;
			// copy size and capacity
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			// allocate new array and copy elements from other
			mData = new T[mCapacity];
			for (mData[i]; i < mSize; ++i) {
				mData[i] = other.mData[i];
			}
			// return a reference to this object
			return *this;
		}
	protected:
		/// @brief Increases and double the capacity of the internal array
		void grow();
	};

	template <class T>
	void ArrayList<T>::append(T val) {
		// check if we need to grow before appending
		if (mSize == mCapacity)
			grow();
			
		// Stick our new element in the last slot and (sneakily) increase our size in the process
		mData[mSize++] = val;
	}

	template <class T>
	void ArrayList<T>::clear() {
		if (mData)
			delete[] mData;
		mData = nullptr;
		mSize = 0;
	}

	template <class T>
	// added const b/c the function does not modify the data
	int ArrayList<T>::find(T val, int start_index) const {
		if (start_index >= mSize || start_index < 0)
			throw std::out_of_range("Invalid index: " + std::to_string(start_index));

		for (int i = start_index; i < mSize; i++) {
			if (mData[i] == val)
				return i;
		}

		// We didn't find it
		return -1;
	}

	template <class T>
	// added const b/c the function does not modify the data
	T ArrayList<T>::get(int index) const {
		if (index >= mSize || index < 0)
			throw std::out_of_range("Invalid index: " + std::to_string(index));
			
		return mData[index];
	}

	template <class T>
	void ArrayList<T>::insert(T val, int index) {
		if (index > mSize) {
			throw std::out_of_range("Invalid index: " + std::to_string(index));
		}

		//check if we need to grow before appending
		if (mSize == mCapacity)
			grow();

		// move all the elements that come *after* index up one spot
		for (int i = mSize; i > index; i--) 
			mData[i] = mData[i - 1];
			
		// Put our element in spot index and increase our size 
		mData[index] = val;
		mSize++;
	}

	template <class T>
	T ArrayList<T>::remove(int index) {
		if (index >= mSize || index < 0)
			throw std::out_of_range("Invalid index: " + std::to_string(index));

		// Get the value we'll return at the end (the element removed)
		T result = mData[index];

		// Move all the elements that come after index down one spot
		for (int i = index; i < mSize - 1; i++)
			mData[i] = mData[i + 1];

		// Re-allocate the array (the reverse of a grow operation)
		T* new_array = new T[mSize - 1];
		for (int i = 0; i < mSize - 1; i++)
			new_array[i] = mData[i];
		delete[] mData;
		mData = new_array;

		// Decrease our size
		mSize--;

		// Return the result
		return result;
	}

	template <class T>
	int ArrayList<T>::remove_all(T val) {
		int cur_index = 0;
		int num_removed = 0;
		while (cur_index >= 0 && cur_index < mSize) {
			// Find the next occurrence of val, starting at current position
			cur_index = find(val, cur_index);
			if (cur_index >= 0) {
				// We found one!
				remove(cur_index);
				num_removed++;
			}
		}

		return num_removed;
	}

	template <class T>
	// added const b/c the function does not modify the data
	int ArrayList<T>::size() const {
		return mSize;
	}

	template <class T>
	void ArrayList<T>::grow() {
		// If empty, make it 1 element
		// If not empty, double the size
		int new_capacity = (mCapacity == 0)? 1 : mCapacity * 2;

		// Allocate what will become the new array
		T* new_array = new T[new_capacity];

		// Copy over data from the old array (if any)
		for (int i = 0; i < mSize; i++)
			new_array[i] = mData[i];

		// Destroy the old array
		delete[] mData;

		// Make the new array *the* array
		mData = new_array;
		// update the capacity
		mCapacity = new_capacity;
	}
}