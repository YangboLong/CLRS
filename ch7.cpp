#include <iostream> // std::cout

class Solution{
public:
	void Swap(int &a, int &b){
		int tmp = a;
		a = b;
		b = tmp;
	}
	// quicksort clrs p171
	int Partition(int A[], int p, int q){
		int x = A[p];
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
	void Quicksort(int A[], int p, int r){
		if(p < r){
			int q = Partition(A, p, r);
			Quicksort(A, p, q - 1);
			Quicksort(A, q + 1, r);
		}
	}
	// equal element quicksort, clrs p174 7.1-2
	// all array elements are the same, returns i = (p + q) / 2
	// it still has nlgn instead of n^2 time complexity
	int EqualElementPartition(int A[], int p, int q){
		int x = A[p];
		int i = p;
		for(int j = p + 1; j <= q; j++){
			if(A[j] < x){
				i++;
				Swap(A[i], A[j]);
			}
			else if(A[j] == x){
				// partition in the middle for all equal elements
				if(i <= (p + q) / 2){
					i++;
					Swap(A[i], A[j]);
				}
			}
		}
		Swap(A[p], A[i]);

		return i;
	}
	void EqualElementQuicksort(int A[], int p, int r){
		if(p < r){
			int q = EqualElementPartition(A, p, r);
			EqualElementQuicksort(A, p, q - 1);
			EqualElementQuicksort(A, q + 1, r);
		}
	}
	// clrs p185 7-1 hoare partition correctness
	int HoarePatition(int A[], int p, int q){
		int x = A[p];
		int i = p - 1;
		int j = q + 1;
		while(true){
			do{
				i++;
			} while(A[i] < x);
			do{
				j++;
			} while(A[j] > x);
			if(i < j)
				Swap(A[i], A[j]);
			else
				return j;
		}
	}
	void HoareQuicksort(int A[], int p, int r){
		if(p >= r)
			return;

		int q = HoarePatition(A, p, r);
		HoareQuicksort(A, p, q - 1);
		HoareQuicksort(A, q + 1, r);
	}
	// clrs p186 7-2 quicksort with equal element values 
	// refer to http://www.douban.com/note/219642993/
	void ThreeWayQuicksort(int A[], int l, int r){
		if(l >= r)
			return;

		int x = A[l]; // pivot is selected as the left most element
		int left = l + 1, lflag = l + 1; // left pointers
		int right = r, rflag = r; // right pointers

		while(true){
			while(A[left] <= x && left <= r){
				// if an element is equal to pivot, then swap it with A[lflag]
				if(A[left] == x){
					Swap(A[left], A[lflag]);
					lflag++;
				}
				left++;
			}
			while(A[right] >= x && right > l){
				// if an element is equal to pivot, then swap it with A[rflag]
				if(A[right] == x){
					Swap(A[right], A[rflag]);
					rflag--;
				}
				right--;
			}

			if(left >= right)	break;

			// swap a bigger element (than pivot) on the left with a smaller one on the right
			Swap(A[left], A[right]);
			left++;
			right--;
		}

		// swap the equal elements on the left to the middle
		left--;
		lflag--;
		while(lflag >= l){
			Swap(A[left], A[lflag]);
			left--;
			lflag--;
		}
		// swap the equal elements on the right to the middle
		right++;
		rflag++;
		while(rflag <= r){
			Swap(A[right], A[rflag]);
			right++;
			rflag++;
		}

		// recursively call the function
		ThreeWayQuicksort(A, l, left);
		ThreeWayQuicksort(A, right, r);
	}
};

int main()
{
	// unit test
	int A[] = {2, 8, 7, 1, 3, 5, 6, 4};
	std::cout << "Unsorted array A entries: ";
	for(int i = 0; i < 8; i++){
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
	
	Solution sln;
	sln.Quicksort(A, 0, 7);
	std::cout << "Sorted array A entries: ";
	for(int i = 0; i < 8; i++){
		std::cout << A[i] << " ";
	}
	std::cout << std::endl;
	
	//int B[] = {1, 1, 1, 1, 1, 1, 1, 1}; // all elements are equal
	int B[] = {1, 5, 1, 1, 2, 1, 1, 1};
	std::cout << "Unsorted array B entries: ";
	for(int i = 0; i < 8; i++){
		std::cout << B[i] << " ";
	}
	std::cout << std::endl;
	
	sln.EqualElementQuicksort(B, 0, 7);
	std::cout << "Sorted array B entries: ";
	for(int i = 0; i < 8; i++){
		std::cout << B[i] << " ";
	}
	std::cout << std::endl;

	int C[] = {13, 19, 9, 5, 12, 8, 7, 4, 11, 2, 6, 21};
	std::cout << "Unsorted array C entries: ";
	for(int i = 0; i < 12; i++){
		std::cout << C[i] << " ";
	}
	std::cout << std::endl;
	
	sln.EqualElementQuicksort(C, 0, 11);
	std::cout << "Sorted array C entries: ";
	for(int i = 0; i < 12; i++){
		std::cout << C[i] << " ";
	}
	std::cout << std::endl;
	int D[] = {2, 1, 2, 4, 3};
	std::cout << "Unsorted array D entries: ";
	for(int i = 0; i < 5; i++){
		std::cout << D[i] << " ";
	}
	std::cout << std::endl;
	
	sln.ThreeWayQuicksort(D, 0, 4);
	std::cout << "Sorted array D entries: ";
	for(int i = 0; i < 5; i++){
		std::cout << D[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}