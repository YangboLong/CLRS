#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <algorithm>

class Solution{
public:
	// clrs p214
	int* GetMinMax(std::vector<int>& A){
		int min, max;
		int* ret = new int[2]; // cannot return a new array, unless that array was dynamically allocated
		if(A.size() % 2){ // odd elements
			min = A[0];
			max = A[0];
			for(int i = 1; i < A.size(); i++){
				if(A[i] >= A[i+1]){
					if(A[i] > max)
						max = A[i];
					if(A[i+1] < min)
						min = A[i+1];
				}
				else{
					if(A[i] < min)
						min = A[i];
					if(A[i+1] > max)
						max = A[i+1];
				}
				i++; // move to next pair of elements
			}
		}
		else{ // even elements
			if(A[0] >= A[1]){
				min = A[1];
				max = A[0];
			}
			else{
				min = A[0];
				max = A[1];
			}
			for(int i = 2; i < A.size(); i += 2){
				if(A[i] >= A[i+1]){
					if(A[i] > max)
						max = A[i];
					if(A[i+1] < min)
						min = A[i+1];
				}
				else{
					if(A[i] < min)
						min = A[i];
					if(A[i+1] > max)
						max = A[i+1];
				}
			}
		}
		ret[0] = min;
		ret[1] = max;
		
		return ret;
	}
	// clrs p216, returns the ith smallest item in A
	int RandomizedSelect(std::vector<int>& A, int p, int r, int i){
		if(i <= 0 || i > A.size())
			return std::numeric_limits<int>::min();

		if(p == r)
			return A[p];
		int q = RandomizedPartition(A, p, r);
		int k = q - p + 1;
		if(i == k) // the pivot value is the answer
			return A[q];
		else if(i < k)
			return RandomizedSelect(A, p, q - 1, i);
		else
			return RandomizedSelect(A, q + 1, r, i - k);
	}
	int RandomizedPartition(std::vector<int>& A, int p, int q){
		int x = A[p]; // pivot value (not randomized here)
		int i = p;
		for(int j = p + 1; j <= q; j++){
			if(A[j] <= x){
				i++;
				Swap(A[i], A[j]);
			}
		}
		Swap(A[p], A[i]);
		
		return i;
	}
	void Swap(int &a, int &b){
		int tmp = a;
		a = b;
		b = tmp;
	}
	// clrs p223, 9.3-8
	double MedOfTwoSortedArr(std::vector<int> X, int begin1, int end1, std::vector<int> Y, int begin2, int end2){
		if(end1 - begin1 != end2 - begin2){
			std::cerr << "Array sizes don't equal." << std::endl;
			exit(EXIT_FAILURE);
		}
		
		int len = end1 - begin1 + 1;
		if(len == 1) // base
			return (X[begin1] + Y[begin1]) / 2.0;
		if(len == 2){ // base
			int tmp = X[begin1] + X[end1] + Y[begin2] + Y[end2];
			tmp -= (std::min(X[begin1], Y[begin2]) + std::max(X[end1], Y[end2]));
			return tmp / 2.0;
		}
		if(X[(begin1 + end1) / 2] < Y[(begin2 + end2) / 2]){
			if(len % 2 == 0) // even elements
				return MedOfTwoSortedArr(X, (begin1 + end1) / 2, end1, Y, begin2, (begin2 + end2) / 2 + 1);
			else // odd elements
				return MedOfTwoSortedArr(X, (begin1 + end1) / 2, end1, Y, begin2, (begin2 + end2) / 2);
		}
		else{
			if(len % 2 == 0)
				return MedOfTwoSortedArr(X, begin1, (begin1 + end1) / 2 + 1, Y, (begin2 + end2) / 2, end2);
			else
				return MedOfTwoSortedArr(X, begin1, (begin1 + end1) / 2, Y, (begin2 + end2) / 2, end2);
		}
	}
};

int main(){
	int a[] = {1, -2, 3, 5, -2, -6, 0, 12, -3, -8};
	//int a[] = {1, -2, 3, 5, -2, -6, 0, 12, -3, -8, 123};
	std::vector<int> A(a, a + sizeof(a) / sizeof(int));
	std::cout << "The array entries are:";
	for (std::vector<int>::iterator it = A.begin(); it != A.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	Solution sln;
	int* b = sln.GetMinMax(A);
	std::cout << "The min element is: " << *b << std::endl;
	std::cout << "The max element is: " << *(b+1) << std::endl;
	delete [] b;

	int c[] = {7, 8, 6, 10, 9};
	std::vector<int> C(c, c + sizeof(c) / sizeof(int));
	std::cout << "Array entries:";
	for (std::vector<int>::iterator it = C.begin(); it != C.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	int d = sln.RandomizedSelect(C, 0, C.size() - 1, 3);
	std::cout << "The 3rd smallest element is: " << d << std::endl;

	int x[] = {1, 2, 3, 4, 5};
	int y[] = {-4, -3, 2, 4, 7};
	std::vector<int> X(x, x + sizeof(x) / sizeof(int));
	std::vector<int> Y(y, y + sizeof(y) / sizeof(int));
	std::cout << "Array X:";
	for (std::vector<int>::iterator it = X.begin(); it != X.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
	std::cout << "Array Y:";
	for (std::vector<int>::iterator it = Y.begin(); it != Y.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;

	double median = sln.MedOfTwoSortedArr(X, 0, X.size() - 1, Y, 0, Y.size() - 1);
	std::cout << "The median of X and Y is: " << median << std::endl;

	return 0;
}