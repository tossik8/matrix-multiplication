#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>
#include <regex>

using namespace std;

vector<vector<double>> multiplyMatrices(vector<vector<double>>& a, vector<vector<double>>& b) {
	vector<vector<double>> c;
	for (int row = 0; row < a.size(); ++row) {
		vector<double> rowVector;
		for (int col = 0; col < b.size(); ++col) {
			double value = 0;
			for (int el = 0; el < b[col].size(); ++el) {
				value += a[row][el] * b[col][el];
			}
			rowVector.push_back(value);
		}
		c.push_back(rowVector);
	}
	return c;
}

vector<vector<double>> addMatrices(vector<vector<double>>& a, vector<vector<double>>& b) {
	vector<vector<double>> c;
	for (int i = 0; i < a.size(); ++i) {
		vector<double> row;
		double value = 0;
		for (int j = 0; j < a[0].size(); ++j) {
			value = a[i][j] + b[i][j];
			row.push_back(value);
		}
		c.push_back(row);
	}
	return c;
}
vector<vector<double>> subtractMatrices(vector<vector<double>>& a, vector<vector<double>>& b) {
	vector<vector<double>> c;
	for (int i = 0; i < a.size(); ++i) {
		vector<double> row;
		double value = 0;
		for (int j = 0; j < a[0].size(); ++j) {
			value = a[i][j] - b[i][j];
			row.push_back(value);
		}
		c.push_back(row);
	}
	return c;
}

void printMatrix(vector<vector<double>> c) {
	for (int i = 0; i < c.size(); ++i) {
		for (int j = 0; j < c[0].size(); ++j) {
			cout << c[i][j] << ' ';
		}
		cout << '\n';
	}
}

vector<vector<double>> createMatrix(string axis) {
	cout << "To write a " << axis << " in a matrix, type numbers in 1 line separated by 1 space\n"
		<< "Once you've finished writing the matrix, type 'Done'\n";
	vector<vector<double>> a;
	string row, splitValue;
	cout << "Input " << axis << '\n';
	getline(cin, row);
	while (row != "Done") {
		vector<double> rowVector;
		stringstream s(row);
		bool isValid = true;
		while (getline(s, splitValue, ' ')) {
			double value;
			try {
				value = stod(splitValue);
			}
			catch (invalid_argument e) {
				isValid = false;
				rowVector.clear();
				rowVector.shrink_to_fit();
				cout << splitValue << " is not a number\n";
			}
			if (isValid) {
				rowVector.push_back(value);
			}
		}
		if (isValid) {
			a.push_back(rowVector);
		}
		row = "";splitValue = "";
		cout << "Input " << axis << '\n';
		getline(cin, row);
	} 
	return a;
}

bool checkMatrix(vector<vector<double>>& a) {
	for (int i = 0; i < a.size(); ++i) {
		if (a[i].size() != a[0].size()) return false;
	}
	return true;
}
bool checkMatrices(vector<vector<double>>& a, vector<vector<double>>& b) {
	return a[0].size() == b[0].size();
}

vector<vector<double>> transposeMatrix(vector<vector<double>>& a) {
	vector<vector<double>> b;
	for (int i = 0; i < a[0].size(); ++i) {
		vector<double> col;
		for (int j = 0; j < a.size(); ++j) {
			col.push_back(a[j][i]);
		}
		b.push_back(col);
	}
	return b;
}

void printMenu() {
	cout << "1 - Multiply matrices\n"
		<< "2 - Add matrices\n"
		<< "3 - Subtract matrices\n"
		<< "4 - Quit";
}

bool createAndCheck(vector<vector<double>>& a, vector<vector<double>>& b, string axisA, string axisB) {
	cout << "First matrix\n";
	a = createMatrix(axisA);
	if (!checkMatrix(a)) {
		return false;
	}
	cout << '\n';
	printMatrix(a);
	cout << "\nSecond matrix\n";
	b = createMatrix(axisB);
	if (!checkMatrix(b)) {
		return false;
	}
	cout << '\n';
	return checkMatrices(a,b);
}

int main() {
	cout << "You've started \"Matrix Multiplicator\"\n\n";
	while (true) {
		printMenu();
		cout << "\nInput command: ";
		int command;
		cin >> command;
		if (cin.fail()) {
			cout << "Only numbers are accepted\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		vector<vector<double>> a, b;
		cin.clear();
		cin.ignore();
		switch (command) {
			case 1: 
				if (!createAndCheck(a, b, "row", "column")) {
					cout << "The format of the matrix is incorect or matrices cannot be multiplied together\n";
					continue;
				}
				printMatrix(transposeMatrix(b));
				cout << "\nResult\n\n";
				printMatrix(multiplyMatrices(a, b));
				cout << '\n';
				break;
			case 2:
				if (!createAndCheck(a, b, "row", "row")) {
					cout << "The format of the matrix is incorect or matrices cannot be sumed up\n";
					continue;
				}
				printMatrix(b);
				cout << "\nResult\n\n";
				printMatrix(addMatrices(a, b));
				cout << '\n';
				break;
			case 3:
				if (!createAndCheck(a, b, "row", "row")) {
					cout << "The format of the matrix is incorect or matrices cannot be subtracted from one another\n";
					continue;
				}
				printMatrix(b);
				cout << "\nResult\n\n";
				printMatrix(subtractMatrices(a, b));
				cout << '\n';
				break;
			case 4:
				cout << "Exiting...\n";
				return 0;
			default:
				cout << "Operation " << command << " doesn't exist\n";
		}
	}
}
