#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>

int CutRod(int [], int);
int MemoizedCutRod(int [], int);
int MemoizedCutRodAux(int [], int, std::vector<int>);
int BottomUpCutRod(int [], int);
std::vector<std::vector<int>> ExtendedBottomUpCutRod(int [], int);

int main()
{
	int p[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
	int n = 10;
	int revenue1 = CutRod(p, n);
	int revenue2 = MemoizedCutRod(p, n);
	int revenue3 = BottomUpCutRod(p, n);
	std::vector<std::vector<int>> revenue4 = ExtendedBottomUpCutRod(p, n);
	while(n > 0) {
		std::cout << revenue4[1][n] << " ";
		n -= revenue4[1][n];
	}

	return 0;
}

int CutRod(int p[], int n) {
	if(n == 0)
		return 0;

	int q = std::numeric_limits<int>::min();
	
	for(int i = 0; i < n; i++) {
		q = std::max(q, p[i] + CutRod(p, n - 1 - i));
	}

	return q;
}

int MemoizedCutRod(int p[], int n) {
	// save the result of each subproblem
	std::vector<int> r(n + 1);

	for(int i = 0; i < n + 1; i++) {
		r[i] = std::numeric_limits<int>::min();
	}

	return MemoizedCutRodAux(p, n, r);
}

int MemoizedCutRodAux(int p[], int n, std::vector<int> r) {
	// first check if it has previously solved this subproblem
	if(r[n] >= 0)
		return r[n];
	int q;

	if(n == 0)
		q = 0;
	else {
		q = std::numeric_limits<int>::min();
		for(int i = 0; i < n; i++) {
			q = std::max(q, p[i] + MemoizedCutRodAux(p, n - 1 - i, r));
		}
	}
	r[n] = q; // save the result of a subproblem
	
	return q;
}

int BottomUpCutRod(int p[], int n) {
	// save the result of the subproblems
	std::vector<int> r(n + 1);

	r[0] = 0;
	for(int j = 1; j < n + 1; j++) {
		int q = std::numeric_limits<int>::min();
		for(int i = 0; i < j; i++) {
			q = std::max(q, p[i] + r[j - 1 - i]);
		}
		r[j] = q;
	}

	return r[n];
}

std::vector<std::vector<int>> ExtendedBottomUpCutRod(int p[], int n) {
	// save the result of the subproblems
	std::vector<int> r(n + 1);
	// save the optimal size i of the first piece to cut off when solving a subproblem of size j
	std::vector<int> s(n + 1);
	// save the return value
	std::vector<std::vector<int>> t(2);

	r[0] = 0;
	for(int j = 1; j < n + 1; j++) {
		int q = std::numeric_limits<int>::min();
		for(int i = 0; i < j; i++) {
			if(q < p[i] + r[j - 1 - i]) {
				q = p[i] + r[j - 1 - i];
				s[j] = i + 1;
			}
		}
		r[j] = q;
	}

	t[0] = r;
	t[1] = s;

	return t;
}