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
			// start
		}

	public: 
		HashMap() : capacity(10), size(0), loadFactor(0.75) {
			// start
		}

		~HashMap() {
			delete[] array;
		}

		V& operator[](const K& key) const {
			// implement
		}
	};
}