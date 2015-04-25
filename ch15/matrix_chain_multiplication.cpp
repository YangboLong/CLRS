#include <iostream>
#include <vector>
#include <utility> // std::pair
#include <limits>

#define ROW 3
#define COL 2

std::vector<std::vector<int>> MatrixMultiply(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> MatrixChainOrder(std::vector<int>);
void PrintOptimalParens(std::vector<std::vector<int>>, int, int);

int main() {
	std::vector<std::vector<int>> A(ROW, std::vector<int>(COL));
	A[0][0] = 1, A[0][1] = 3;
	A[1][0] = 2, A[1][1] = 4;
	A[2][0] = 3, A[2][1] = 5;
	std::vector<std::vector<int>> B(COL, std::vector<int>(ROW));
	B[0][0] = 1, B[0][1] = 2, B[0][2] = 3;
	B[1][0] = 3, B[1][1] = 4, B[1][2] = 5;
	std::vector<std::vector<int>> C(ROW, std::vector<int>(ROW));

	C = MatrixMultiply(A, B);

	int arr[] = {30, 35, 15, 5, 10, 20, 25};
	std::vector<int> p(arr, arr + sizeof(arr) / sizeof(arr[0]));
	std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> P = MatrixChainOrder(p);

	PrintOptimalParens(P.second, 0, 5);

	return 0;
}

std::vector<std::vector<int>> MatrixMultiply(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
	if(A[0].size() != B.size()) {
		std::cerr << "incompatible dimensions" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<std::vector<int>> C(A.size(), std::vector<int>(B[0].size()));
	for(int i = 0; i < A.size(); i++) {
		for(int j = 0; j < B[0].size(); j++) {
			C[i][j] = 0;
			for(int k = 0; k < A[0].size(); k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return C;
}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> MatrixChainOrder(std::vector<int> p) {
	int n = p.size() - 1;
	std::vector<std::vector<int>> m(n, std::vector<int>(n)); // storing the scalar multiplication, m[i, j], costs
	std::vector<std::vector<int>> s(n, std::vector<int>(n)); // storing the index of k that achieved the optimal cost

	// minimum costs for chains of length 1
	for(int i = 0; i < n; i++) {
		m[i][i] = 0;
	}

	for(int l = 1; l < n; l++) { // l is the length of chain
		for(int i = 0; i < n - l; i++) {
			int j = i + l;
			m[i][j] = std::numeric_limits<int>::max();
			for(int k = i; k < j; k++) {
				int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
				if(q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	return std::make_pair(m, s);
}

void PrintOptimalParens(std::vector<std::vector<int>> s, int i, int j) {
	if(i == j)
		std::cout << "A" << i + 1;
	else {
		std::cout << "(";
		PrintOptimalParens(s, i, s[i][j]);
		PrintOptimalParens(s, s[i][j] + 1, j);
		std::cout << ")";
	}
}