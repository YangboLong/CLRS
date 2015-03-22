#include <iostream>
#include <vector>

class Solution{
public:
	// clrs p195
	void CountingSort(std::vector<int> &A, int B[], int k){
		std::vector<int> C;
		for(int i = 0; i <= k; i++){
			C.push_back(0);
		}
		for(int j = 0; j < A.size(); j++){
			C[A[j]]++;
		}
		for(int i = 1; i <= k; i++){
			C[i] += C[i-1];
		}
		for(int j = A.size() - 1; j >= 0; j--){
			B[C[A[j]] - 1] = A[j];
			C[A[j]]--;
		}
		/*for(int j = 0; j < A.size(); j++){
			B[C[A[j]] - 1] = A[j];
			C[A[j]]--;
		}*/
	}

	// clrs p198
	void RadixSort(std::vector<int> &A, int d){
		int exp = 1;
		int C[10];
		/*int *B = new int[A.size()];
		for(int i = 0; i < A.size(); i++){
			B[i] = 0;
		}*/
		for(int i = 0; i < 10; i++){
			C[i] = 0;
		}
		for(int digits = 0; digits < d; digits++){
			int *B = new int[A.size()];

			for(int j = 0; j < A.size(); j++){
				C[(A[j]/exp) % 10]++;
			}
			for(int i = 1; i < 10; i++){
				C[i] += C[i-1];
			}
			for(int j = A.size() - 1; j >= 0; j--){
				B[C[(A[j]/exp) % 10] - 1] = A[j];
				C[(A[j]/exp) % 10]--;
			}
			for(int k = 0; k < A.size(); k++){
				A[k] = B[k];
				//B[k] = 0;
			}
			for(int i = 0; i < 10; i++){
				C[i] = 0;
			}
			exp *= 10;
			delete [] B;
		}
		//delete [] B;
	}
};

int main(){
	Solution sln;
	int inta[] = {2, 5, 3, 0, 2, 3, 0, 3};
	std::vector<int> A(inta, inta + sizeof(inta) / sizeof(int));

	int B[8];
	std::cout << "Unsorted array A entries: ";
	for(int i = 0; i < A.size(); i++){
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;

	sln.CountingSort(A, B, 5);
	std::cout << "Sorted array B entries: ";
	for(int i = 0; i < 8; i++){
		std::cout << B[i] << " ";
	}
	std::cout << std::endl;
	
	int intd[] = {32, 4, 657, 839, 436, 720, 355};
	std::vector<int> D(intd, intd + sizeof(intd) / sizeof(int));
	
	std::cout << "Unsorted array D entries: ";
	for(int i = 0; i < D.size(); i++){
		std::cout << D[i] << " ";
	}
	std::cout << std::endl;

	sln.RadixSort(D, 3);
	std::cout << "Sorted array D entries: ";
	for(int i = 0; i < D.size(); i++){
		std::cout << D[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}