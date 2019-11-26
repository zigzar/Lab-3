#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ofstream fout;

template <size_t N>
void coutMatrix(int(&A)[N][N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
}

template <size_t N>
void foutMatrix(int(&A)[N][N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fout << A[i][j] << "\t";
		}
		fout << endl;
	}
}

template <size_t N>
void fillSnake(int (&A)[N][N], int count) {
	for (int j = 0; j < N;)
	{
		for (int i = 0; i < N; i++)
		{
			A[i][j] = count++;
			system("cls");
			coutMatrix(A);
		}
		j++;
		if (j == N) break;
		for (int i = N - 1; i >= 0; i--)
		{
			A[i][j] = count++;
			system("cls");
			coutMatrix(A);
		}
		j++;
		if (j == N) break;
	};
};

template <size_t N>
void fillRight(int (&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curCol++) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A);
	}
	curCol--;
	curRow++;
}

template <size_t N>
void fillDown(int(&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curRow++) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A);
	}
	curCol--;
	curRow--;
}

template <size_t N>
void fillLeft(int(&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curCol--) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A);
	}
	curCol++;
	curRow--;
}

template <size_t N>
void fillUp(int(&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curRow--) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A);
	}
	curCol++;
	curRow++;
}

template <size_t N>
void fillDirectional(int (&A)[N][N],int length, int &curRow, int &curCol, int &direction, int &count) {
	switch (direction%4)
	{
	case 0:
		fillRight(A, length, curRow, curCol, count);
		break;
	case 1:
		fillDown(A, length, curRow, curCol, count);
		break;
	case 2:
		fillLeft(A, length, curRow, curCol, count);
		break;
	case 3:
		fillUp(A, length, curRow, curCol, count);
		break;
	}
	direction++;
}

template <size_t N>
void fillSpiral(int(&A)[N][N], int start) {
	int count = start;
	int direction = 0;
	int curRow = 0;
	int curCol = 0;
	for (int length = N; length > 0; length--)
	{
		if (length == N) {
			fillDirectional(A, length, curRow, curCol, direction, count);
		} else if (length > 0) {
			for (int i = 0; i < 2; i++) {
				fillDirectional(A, length, curRow, curCol, direction, count);
			}
		}
	}
}

int main()
{
	setlocale(0, "");


	string path = "matrix.txt";
	int Order = 11;

	int **matrix = int* [Order];
	for (int i = 0; i < Order; i++)
	{
		matrix[i] = int[Order];
	}
	
	int method, start;

	while (true)
	{
		cout << "Выберите способ заполнения:" << endl;
		cout << "1 - змейкой," << endl;
		cout << "2 - спиралью" << endl;
		cout << endl;
		cin >> method;

		cout << "Введите число, с которого начнётся заполнение: ";
		cin >> start;
		switch (method)
		{
		case 1:
			fillSnake(matrix, start);
			goto inpSucc;
			break;
		case 2:
			fillSpiral(matrix, start);
			goto inpSucc;
			break;
		default:
			cout << "Ошибка ввода! Пожалуйста, используйте «1» или «2» для выбора метода заполнения" << endl;
			break;
		}
	}

	inpSucc:
	fout.open(path);
	try
	{
		foutMatrix(matrix);
	}
	catch (const exception&)
	{
		cout << "Ошибка записи файла!" << endl;
	}
	fout.close();

	for (int i = 0; i < Order; i++)
	{
		delete [] matrix[i];
	}
	delete[] matrix;
}
