#include <iostream>
#include <array>

using namespace std;

array<array<int, 4>,2> computeMatrix(array<array<int,4>,2> a, array<array<int, 4>,4> b) {
	array<array<int, b.size()>, a.size()> c;
	for (int row = 0; row < a.size(); ++row) {
		for (int col = 0; col < b.size(); ++col) {
			int value = 0;
			for (int el = 0; el < b[col].size(); ++el) {
				value += a[row][el] * b[col][el];
			}
			c[row][col] = value;
		}
	}
	return c;
}

int main() {
	array<array<int,4>, 4> b = { {
		{2,3,7, 4},
		{6,8,1, 20},
		{9,0,11,-2},
		{2,7,10,-4}
	} };
	array<array<int, 4>, 2> a = { {
		{2,3,9, -1},
		{6,8,0,1}
	} };
	array<array<int,4>,2> c = computeMatrix(a, b);
	
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size(); ++j) {
			std::cout << c[i][j]<< ' ';
		}
		std::cout << '\n';
	}
}

