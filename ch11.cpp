// clrs p270 - ch11 - hashing by open addressing (linear probing)
#include <iostream>

class Solution {
public:
	Solution(int n) {
		length = n;

		table = new SLOT [n];
		for(int i = 0; i < n; i++) {
			table[i].stat = INVALID;
		}
	}

	~Solution() {
		delete [] table;
	}

	int HashInsert(int key) {
		int h_prime = key % length; // auxiliary hash function

		for(int i = 0; i < length; i++) {
			int h = (i + h_prime) % length; // hash function - linear probing

			if(table[h].stat == INVALID || table[h].stat == DELETED) {
				table[h].key = key;
				table[h].stat = OCCUPIED;

				return h; // hash function is also the index of hash table
			}
		}

		return -1;
	}

	int HashSearch(int key) {
		int h_prime = key % length;

		for(int i = 0; i < length; i++) {
			int h = (i + h_prime) % length;

			if(table[h].stat == OCCUPIED && table[h].key == key) {
				return h;
			}

			if(table[h].stat == INVALID || table[h].stat == DELETED) {
				return -1;
			}
		}

		return -1;
	}

	bool HashDelete(int key) {
		int h_prime = key % length;

		for(int i = 0; i < length; i++) {
			int h = (i + h_prime) % length;

			if(table[h].stat == OCCUPIED && table[h].key == key) {
				table[h].stat = DELETED;
				return true;
			}

			if(table[h].stat == INVALID || table[h].stat == DELETED)
				return false;
		}

		return false;
	}

private:
	enum STATUS {
		INVALID,
		DELETED,
		OCCUPIED,
	};
	struct SLOT {
		int key;
		STATUS stat;
	};
	SLOT* table;
	int length;
};

int main() {
	Solution sol(10);
	int index1, index2, index3, index4, index5;
	index1 = sol.HashInsert(5);
	index2 = sol.HashInsert(0);
	index3 = sol.HashInsert(33);

	index4 = sol.HashSearch(5);
	sol.HashDelete(5);
	index5 = sol.HashSearch(5);

	return 0;
}