#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

vector<vector<double>> multiplyMatrices(vector<vector<double>>& a, vector<vector<double>>& b) {
	vector<vector<double>> c;
	for (int row = 0; row < a.size(); ++row) {
		vector<double> rowVector;
		for (int col = 0; col < b[0].size(); ++col) {
			double value = 0;
			for (int el = 0; el < b.size(); ++el) {
				value += a[row][el] * b[el][col];
			}
			rowVector.push_back(value);
		}
		c.push_back(rowVector);
	}
	return c;
}

vector<vector<double>> multiplyByFactor(vector<vector<double>>& a, double& factor) {
	for (int row = 0; row < a.size(); ++row) {
		for (int col = 0; col < a[row].size(); ++col) {
			a[row][col] *= factor;
		}
	}
	return a;
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

vector<vector<double>> createMatrix() {
	cout << "To write a row in a matrix, type numbers in 1 line separated by 1 space\n"
		<< "Once you've finished writing the matrix, type 'Done'\n";
	vector<vector<double>> a;
	string row, splitValue;
	cout << "Input row\n";
	getline(cin, row);
	while (row != "Done") {
		if (row == "") {
			cout << "Cannot be empty\nInput row\n";
			getline(cin, row);
			continue;
		}
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
		row = ""; splitValue = "";
		cout << "Input row\n";
		getline(cin, row);
	}
	return a;
}

bool checkMatrix(vector<vector<double>>& a) {
	for (int i = 0; i < a.size(); ++i) {
		if (a[i].size() != a[0].size()) return false;
	}
	return a.size() != 0 && true;
}
bool isMultiplicable(vector<vector<double>>& a, vector<vector<double>>& b) {
	return a[0].size() == b.size();
}
bool isAddable(vector<vector<double>>& a, vector<vector<double>>& b) {
	return a[0].size() == b[0].size() && a.size() == b.size();
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
		<< "4 - Transpose matrix\n"
		<< "5 - Multiply a matrix by a factor\n"
		<< "6 - Quit";
}

bool createAndCheck(vector<vector<double>>& a, vector<vector<double>>& b) {
	cout << "First matrix\n";
	a = createMatrix();
	if (!checkMatrix(a)) {
		return false;
	}
	cout << '\n';
	printMatrix(a);
	cout << "\nSecond matrix\n";
	b = createMatrix();
	if (!checkMatrix(b)) {
		return false;
	}
	cout << '\n';
	printMatrix(b);
	cout << '\n';
	return true;
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
			if (!createAndCheck(a, b) || !isMultiplicable(a,b)) {
				cout << "Either the format of the matrix is incorect or matrices cannot be multiplied together\n";
				continue;
			}
			cout << "\nResult\n\n";
			printMatrix(multiplyMatrices(a, b));
			cout << '\n';
			break;
		case 2:
			if (!createAndCheck(a, b) || !isAddable(a,b)) {
				cout << "Either the format of the matrix is incorect or matrices cannot be sumed up\n";
				continue;
			}
			cout << "\nResult\n\n";
			printMatrix(addMatrices(a, b));
			cout << '\n';
			break;
		case 3:
			if (!createAndCheck(a, b) || !isAddable(a,b)) {
				cout << "Either the format of the matrix is incorect or matrices cannot be subtracted from one another\n";
				continue;
			}
			cout << "\nResult\n\n";
			printMatrix(subtractMatrices(a, b));
			cout << '\n';
			break;
		case 4:
			a = createMatrix();
			if (checkMatrix(a)) {
				cout << "\nResult\n\n";
				printMatrix(transposeMatrix(a));
				cout << '\n';
			}
			else {
				cout << "The matrix isn't formatted properly\n";
			}
			break;
		case 5:
			a = createMatrix();
			if (checkMatrix(a)) {
				cout << "Enter a factor\n";
				double factor;
				cin >> factor;
				if (cin.fail()) {
					cout << "Only numbers are accepted\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				cout << "\nResult\n\n";
				printMatrix(multiplyByFactor(a, factor));
				cout << '\n';
			}
			else {
				cout << "The matrix isn't formatted properly\n";
			}
			break;
		case 6:
			cout << "Exiting...\n";
			return 0;
		default:
			cout << "Operation " << command << " doesn't exist\n";
		}
	}
}

