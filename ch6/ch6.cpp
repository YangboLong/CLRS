#include <iostream> // std::cout
#include <vector> // std::vector
#include <cstdlib> // exit
#include <limits> // std::numeric_limits
#include <cstdlib> // EXIT_FAILURE

class Solution{
public:
	// maintain the heap property by sinking down, clrs p154
	void MaxHeapify(std::vector<int>& A, int i){
		int l = 2 * (i + 1) - 1, r = 2 * (i + 1), largest;
		if(l <= (int)A.size() - 1 && A[l] > A[i])
			largest = l;
		else
			largest = i;
		if(r <= (int)A.size() - 1 && A[r] > A[largest])
			largest = r;
		if(largest != i){
			int temp = A[i];
			A[i] = A[largest];
			A[largest] = temp;
			MaxHeapify(A, largest);
		}
	}
	// build a maximum heap, clrs p157
	void BuildMaxHeap(std::vector<int>& A){
		for(int i = A.size() / 2 - 1; i >= 0; i--)
			MaxHeapify(A, i);
	}
	// heapsort algorithm, clrs p160
	std::vector<int> Heapsort(std::vector<int> A){
		std::vector<int> res;
		BuildMaxHeap(A);
		int len = A.size();
		for(int i = len - 1; i >= 1; i--){
			std::vector<int>::iterator it = res.begin();
			int temp = A[i];
			A[i] = A[0];
			A[0] = temp;
			res.insert(it, A[i]);
			A.pop_back();
			MaxHeapify(A, 0);
		}
		res.insert(res.begin(), A[0]);
		return res;
	}
	
	// priority queue Maximum operation, clrs p163
	int HeapMax(std::vector<int> &A){
		return A[0];
	}
	// priority queue Extract-Max operation, clrs p163
	int HeapExtMax(std::vector<int> &A){
		int len = A.size();
		if(len < 1){
			std::cerr << "Heap underflow." << std::endl;
			exit(EXIT_FAILURE);
		}
		int max = A[0];
		A[0] = A[len - 1];
		A.pop_back();
		MaxHeapify(A, 0);
		return max;
	}
	// priority queue Increase-Key operation, clrs p164
	void HeapIncKey(std::vector<int> &A, int i, int key){
		if(key < A[i]){
			std::cerr << "New key is smaller than current key." << std::endl;
			exit(EXIT_FAILURE);
		}
		A[i] = key;
		while(i > 0 && A[(i + 1) / 2 - 1] < A[i]){
			int tmp = A[i];
			A[i] = A[(i + 1) / 2 - 1];
			A[(i + 1) / 2 - 1] = tmp;
			i = (i + 1) / 2 - 1;
		}
	}
	// priority queue Insert operation, clrs p164
	void MaxHeapIns(std::vector<int> &A, int key){
		A.push_back(std::numeric_limits<int>::min());
		HeapIncKey(A, A.size() - 1, key);
	}
};

int main(){
	// unit test
	Solution sln;
	int inta[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
	std::vector<int> A(inta, inta + sizeof(inta) / sizeof(int)); // initialize vector from array
	
	std::cout << "The original contents are:";
	for (std::vector<int>::iterator it = A.begin(); it != A.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	std::vector<int> res = sln.Heapsort(A);
	
	std::cout << "The contents in order are:";
	for (std::vector<int>::iterator it = res.begin(); it != res.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	int intb[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};
	std::vector<int> B(intb, intb + sizeof(intb) / sizeof(int));
	std::cout << "Heap B is:";
	for (std::vector<int>::iterator it = B.begin(); it != B.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	std::cout << "Maximum element in B is: " << sln.HeapMax(B) << std::endl;
	sln.HeapIncKey(B, 8, 15);
	std::cout << "The Increase-Key operation:";
	for (std::vector<int>::iterator it = B.begin(); it != B.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	
	sln.HeapExtMax(B);
	std::cout << "The Extract-Max operation:";
	for (std::vector<int>::iterator it = B.begin(); it != B.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	sln.MaxHeapIns(B, 18);
	std::cout << "The Insert operation:";
	for (std::vector<int>::iterator it = B.begin(); it != B.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	return 0;
}