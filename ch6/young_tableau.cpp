// 6-3 young tableaus, clrs p167
#include <iostream> // std::cout
#include <vector> // std::vector
#include <cstdlib> // exit
#include <limits> // std::numeric_limits
#include <cstdlib> // EXIT_FAILURE

#define ROW 4
#define COL 4

class Solution{
public:
	// initialize young tableau elements with positive infinities
	Solution(int row, int col){
		for(int i = 0; i < row; i++)
			for(int j = 0; j < col; j++)
				matrix[i][j] = std::numeric_limits<int>::max();
	}
	void Insert(int key){
		int i = ROW-1, j = COL -1;
		// check if we can insert the element
		// if the last entry in tableau is larger than the element then cannot insert
		if(matrix[i][j] <= key){
			std::cerr << "Cannot insert element." << std::endl;
			exit(EXIT_FAILURE);
		}
		// set the last entry to be the element that we want to insert
		matrix[i][j] = key;
		int threshold = std::numeric_limits<int>::max();
		int larger_i = i, larger_j = j;
		// exchange the element with either the left or the top entry (which ever is larger) 
		// until we obtain a valid young tableau
		while((i > 0 || j > 0) && (matrix[i][j] < threshold)){
			int tmp = matrix[i][j];
			matrix[i][j] = matrix[larger_i][larger_j];
			matrix[larger_i][larger_j] = tmp;
			i = larger_i;
			j = larger_j;
			if(i-1 >= 0 && matrix[i][j] < matrix[i-1][j]){
				larger_i = i - 1;
				larger_j = j;
			}
			if(j-1 >= 0 && matrix[larger_i][larger_j] < matrix[i][j-1]){
				larger_i = i;
				larger_j = j - 1;
			}
			threshold = matrix[larger_i][larger_j];
		}
	}
	int ExtractMin(){
		int ret = matrix[0][0];
		matrix[0][0] = std::numeric_limits<int>::max();
		Youngify(0, 0); // recurrence

		return ret;
	}
	void Youngify(int i, int j){
		int smaller_i = i, smaller_j = j;
		if(i+1 <= ROW-1 && matrix[i][j] > matrix[i+1][j]){
			smaller_i = i + 1;
			smaller_j = j;
		}
		if(j+1 <= COL-1 && matrix[smaller_i][smaller_j] > matrix[i][j+1]){
			smaller_i = i;
			smaller_j = j + 1;
		}
		if(smaller_i != i || smaller_j != j){
			int tmp = matrix[i][j];
			matrix[i][j] = matrix[smaller_i][smaller_j];
			matrix[smaller_i][smaller_j] = tmp;
			Youngify(smaller_i, smaller_j);
		}
	}
	bool IsEmpty(){
		return matrix[0][0] == std::numeric_limits<int>::max();
	}
private:
	int matrix[ROW][COL];
};

int main()
{
	// unit test
	int a[] = {9, 16, 3, 2, 4, 8, 5, 14, 12};
	std::cout << "Unsorted elements in Young tableau:";
	std::vector<int> A(a, a + sizeof(a) / sizeof(int));
	for(int i = 0; i < A.size(); i++){
		std::cout << " " << a[i];
	}
	std::cout << std::endl;
	
	Solution sln(ROW, COL);
	for(int i = 0; i < A.size(); i++){
		sln.Insert(A[i]);
	}

	int i = 0;
	std::cout << "Extracted elements: ";
	while(!sln.IsEmpty()){
		std::cout << sln.ExtractMin() << "->";
	}
	std::cout << "Completed deletion.";

	return 0;
}