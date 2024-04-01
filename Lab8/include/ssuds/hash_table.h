#pragma once

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
					int index = hash(array[i].key) % newCapacity;

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

		V& operator[](const K& key) const {
			// implement
		}

		bool contains(const K& key) const {
			// implement
		}

		void remove(const K& key) const {
			// implement
		}

		friend std::ostream& operator<<(std::ostream& os, const HashMap& hashmap) {
			// implement
		}
	};
}