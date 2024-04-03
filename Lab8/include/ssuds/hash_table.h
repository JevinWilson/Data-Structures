#pragma once

#include <iostream>
#include <functional>

namespace ssuds
{
	template <typename K, typename V>
	class HashMap
	{
	private:
		struct Pair {
			K key;
			V value;
			bool used = false;
			
			Pair() : key(K()), value(V()), used(false) {}
			Pair(K k, V v) : key(k), value(v), used(true) {}
		};

		Pair* array;
		int capacity;
		int size;
		float loadFactor;

		void grow() {
			int newCapacity = capacity * 2;
			Pair* newArray = new Pair[newCapacity];

			for (int i = 0; i < capacity; i++) {
				if (array[i].used) {
					int index = std::hash<K>{}(array[i].key) % newCapacity;

					newArray[index] = array[i];
					newArray[index].used = true;
				}
			}

			delete[] array;
			array = newArray;
			capacity = newCapacity;
		}

	public: 
		HashMap() : capacity(10), size(0), loadFactor(0.75) {
			array = new Pair[capacity];
		}

		~HashMap() {
			delete[] array;
		}

		V& operator[](const K& key) {
			int index = std::hash<K>{}(key) % capacity;
			int originalIndex = index;
			bool found = false;

			do {
				if (!array[index].used) {
					break;
				}
				else if (array[index].used && array[index].key == key) {
					found = true;
					break;
				}
				index = (index + 1) % capacity;                
			} while (index != originalIndex);

			if (!found) {
				if (static_cast<float>(size + 1) / capacity > loadFactor) {
					grow();
					index = std::hash<K>{}(key) % capacity;
				}
				
				index = std::hash<K>{}(key) % capacity; 
				do {
					if (!array[index].used) {
						array[index] = Pair(key, V{});
						array[index].used = true;
						size++;
						break;
					}
					index = (index + 1) % capacity;
				} while (index != originalIndex);
			}

			return array[index].value; 
		}

		// needed to check remove function
		bool contains(const K& key) const {
			int index = std::hash<K>{}(key) % capacity; 
			int originalIndex = index;
			bool found = false;

			do {
				if (!array[index].used) { 
					break;
				} else if (array[index].used && array[index].key == key) { 
					found = true;
					break;
				}
				index = (index + 1) % capacity; 
			} while (index != originalIndex);

			return found;
		}

		class Iterator 
		{
		private:
			const HashMap& hashmap;
			int current;

			Iterator(const HashMap& hashmap, int start) : hashmap(hashmap), current(start) {}

			void nextPos() {
				while (current < hashmap.capacity && !hashmap.array[current].used) {
					current++;
				}
			}

		public:
			friend class HashMap;

			const Pair& operator*() const {
				if (current >= 0 && current < hashmap.capacity && hashmap.array[current].used) {
					return hashmap.array[current];
				}
				throw std::out_of_range("Iterator is out of range");
			}

			Iterator& operator++() {
				current++;
				nextPos();
				return *this;
			}

			Iterator operator++(int) {
				Iterator temp = *this;
				(*this)++;
				return temp;
			}

			bool operator==(const Iterator& other) const {
				return &hashmap == &other.hashmap && current == other.current;
			}

			bool operator!=(const Iterator& other) const {
				return !(*this == other);
			}

		};

		Iterator begin() const {
			Iterator it(*this, 0);
			it.nextPos();
			return it;
		}

		Iterator end() const {
			return Iterator(*this, capacity);
		}

		Iterator find(const K& key) const {
			int index = std::hash<K>{}(key) % capacity;
			int originalIndex = index;

			do {
				if (!array[index].used) {
					break;
				}
				else if (array[index].used && array[index].key == key) {
					return Iterator(*this, index);
				}
				index = (index + 1) % capacity;
			}
			while (index != originalIndex);

			return end();
		}

		bool remove(const K& key) {
			int index = std::hash<K>{}(key) % capacity;
			int originalIndex = index;
			bool found = false;

			do {
				if (!array[index].used) {
					break;
				}
				else if (array[index].used && array[index].key == key) {
					found = true;
					break;
				}
				index = (index + 1) % capacity;
			}
			while (index != originalIndex);

			if (found) {
				array[index].used = false;
				size--;
				return true;
			}
			// nothing found
			return false;
		}

		friend std::ostream& operator<<(std::ostream& os, const HashMap<K, V>& hashmap) {
			os << "{";
			bool first = true;
			for (int i = 0; i < hashmap.capacity; i++) {
				if (hashmap.array[i].used) {
					if (!first) {
						os << ", ";
					}
					os << hashmap.array[i].key << ": " << hashmap.array[i].value;
					first = false;
				}
			}
			os << "}";
			return os;
		}
	};
}