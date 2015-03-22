#include <iostream> // std::cout
#include <vector> // std::vector
#include <limits> // std::numeric_limits

class Solution{
public:
	// get maximum sum of sub-array across middle, clrs p71
	std::vector<int> FindMaxCrossingSubarray(int A[], int low, int mid, int high){
		int left_sum = std::numeric_limits<int>::min();
		int sum = 0, max_left;
		for(int i = mid; i >= low; i--){
			sum = sum + A[i - 1];
			if(sum > left_sum){
				left_sum = sum;
				max_left = i;
			}
		}
		int right_sum = std::numeric_limits<int>::min(), max_right;
		sum = 0;
		for(int i = mid + 1; i <= high; i++){
			sum = sum + A[i - 1];
			if(sum > right_sum){
				right_sum = sum;
				max_right = i;
			}
		}
		std::vector<int> ret;
		ret.push_back(max_left);
		ret.push_back(max_right);
		ret.push_back(left_sum + right_sum);

		return ret;
	}
	// get maximum sub-array of an array, clrs p72
	std::vector<int> FindMaxSubarray(int A[], int low, int high){
		std::vector<int> ret;
		if(low == high){
			ret.push_back(low);
			ret.push_back(high);
			ret.push_back(A[low - 1]);
			return ret;
		}
		else{
			int mid = (low + high) / 2;
			std::vector<int> left = FindMaxSubarray(A, low, mid);
			std::vector<int> right = FindMaxSubarray(A, mid + 1, high);
			std::vector<int> cross = FindMaxCrossingSubarray(A, low, mid, high);
			if(left[2] >= right[2] && left[2] >= cross[2])
				return left;
			else if(right[2] >= left[2] && right[2] >= cross[2])
				return right;
			else
				return cross;
		}
	}
	// maximum sum of subarray in linear time, clrs p75
	std::vector<int> MaxSum(int A[], int low, int high){
		std::vector<int> ret;
		int max_sum = std::numeric_limits<int>::min();
		int left = low, sum = 0, max_left, max_right;
		for(int i = low; i <= high; i++){
			sum += A[i - 1];
			if(sum > max_sum){
				max_sum = sum;
				max_left = left;
				max_right = i;
			}
			if(sum < 0){
				sum = 0;
				left = i + 1;
			}
		}
		ret.push_back(max_left);
		ret.push_back(max_right);
		ret.push_back(max_sum);

		return ret;
	}
};

int main(){
	// unit test
	Solution sln;
	int A[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	std::vector<int> res = sln.FindMaxSubarray(A, 1, 16);
	std::cout << "Using divide-and-conquer alg with nlgn time complexity:" << std::endl;
	std::cout << "The max subarray is from " << res[0] << " to " << res[1] << ", with a sum of " << res[2] << std::endl;
	res = sln.MaxSum(A, 1, 16);
	std::cout << "Using linear time alg:" << std::endl;
	std::cout << "The max subarray is from " << res[0] << " to " << res[1] << ", with a sum of " << res[2] << std::endl;
	
	return 0;
} 