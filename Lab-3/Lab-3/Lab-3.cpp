#include <iostream>
#include <string>
#include <fstream>
#include <vector> 

using namespace std;

ofstream fout;


int getRank(int** A, int N) {
	int rank = N;
	vector<char> line_used(N);
	for (int i = 0; i < N; ++i) {
		int j;
		for (j = 0; j < N; ++j)
			if (!line_used[j] && A[j][i] != 0)
				break;
		if (j == N)
			--rank;
		else {
			line_used[j] = true;
			for (int p = i + 1; p < N; ++p)
				A[j][p] /= A[j][i];
			for (int k = 0; k < N; ++k)
				if (k != j && A[j][i] != 0)
					for (int p = i + 1; p < N; ++p)
						A[k][p] -= A[j][p] * A[k][i];
		}
	}
	return rank;
}


void getMatr(int** A, int** p, int i, int j, int m)
{
	int ki, kj, di, dj;
	di = 0;
	for (ki = 0; ki < m - 1; ki++) {
		if (ki == i) di = 1;
		dj = 0;
		for (kj = 0; kj < m - 1; kj++) {
			if (kj == j) dj = 1;
			p[ki][kj] = A[ki + di][kj + dj];
		}
	}
}
int getDet(int** A, int N) {
	int i, j, d, k, n;
	int** p = new int* [N];
	for (int i = 0; i < N; i++)
		p[i] = new int[N];
	j = 0; d = 0;
	k = 1;
	n = N - 1;
	switch (N)
	{
	case 1:
		d = A[0][0];
		return(d);
		break;
	case 2:
		d = A[0][0] * A[1][1] - A[1][0] * A[0][1];
		return(d);
		break;
	default:
		for (i = 0, j = 0; j < N; j++) {
			getMatr(A, p, 0, j, N);
			d = d + k * A[0][j] * getDet(p, n);
			k = -k;
		}
		return(d);
		break;
	}
}


void coutMatrix(int** A, int N) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j] << "\t";
		}
		cout << endl;
	}
}
void foutMatrix(int** A, int N) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fout << A[i][j] << "\t";
		}
		fout << endl;
	}
}


void fillSnake(int** A, int N, int count) {
	for (int j = 0; j < N;)
	{
		for (int i = 0; i < N; i++)
		{
			A[i][j] = count++;
			system("cls");
			coutMatrix(A, N);
		}
		j++;
		if (j == N) break;
		for (int i = N - 1; i >= 0; i--)
		{
			A[i][j] = count++;
			system("cls");
			coutMatrix(A, N);
		}
		j++;
		if (j == N) break;
	};
};


void fillRight(int** A, int N, int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curCol++) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A, N);
	}
	curCol--;
	curRow++;
}
void fillDown(int **A, int N, int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curRow++) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A, N);
	}
	curCol--;
	curRow--;
}
void fillLeft(int** A, int N, int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curCol--) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A, N);
	}
	curCol++;
	curRow--;
}
void fillUp(int** A, int N, int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curRow--) {
		A[curRow][curCol] = count++;
		system("cls");
		coutMatrix(A, N);
	}
	curCol++;
	curRow++;
}

void fillDirectional(int** A, int N, int length, int &curRow, int &curCol, int &direction, int &count) {
	switch (direction%4)
	{
	case 0:
		fillRight(A, N, length, curRow, curCol, count);
		break;
	case 1:
		fillDown(A, N, length, curRow, curCol, count);
		break;
	case 2:
		fillLeft(A, N, length, curRow, curCol, count);
		break;
	case 3:
		fillUp(A, N, length, curRow, curCol, count);
		break;
	}
	direction++;
}

void fillSpiral(int** A, int N, int start) {
	int count = start;
	int direction = 0;
	int curRow = 0;
	int curCol = 0;
	for (int length = N; length > 0; length--)
	{
		if (length == N) {
			fillDirectional(A, N, length, curRow, curCol, direction, count);
		} else if (length > 0) {
			for (int i = 0; i < 2; i++) {
				fillDirectional(A, N, length, curRow, curCol, direction, count);
			}
		}
	}
}

int main()
{
	setlocale(0, "");


	string path = "matrix.txt";

	cout << "Введите порядок квадратной матрицы:" << endl;
	int Order;
	cin >> Order;

	int **matrix = new int* [Order];
	for (int i = 0; i < Order; i++)
	{
		matrix[i] = new int [Order];
	}

	for (int i = 0; i < Order; i++)
	{
		for (int j = 0; j < Order; j++)
		{
			matrix[i][j] = 0;
		}
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
			fillSnake(matrix, Order, start);
			goto inpSucc;
			break;
		case 2:
			fillSpiral(matrix, Order, start);
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
		foutMatrix(matrix, Order);
	}
	catch (const exception&)
	{
		cout << "Ошибка записи файла!" << endl;
	}
	fout.close();

	int det = getDet(matrix, Order);
	cout << "Определитель матрицы: " << det << endl;
	int rank = getRank(matrix, Order);
	cout << "Ранк матрицы " << rank << endl;
	

	for (int i = 0; i < Order; i++)
	{
		delete [] matrix[i];
	}
	delete[] matrix;

	system("pause");
}
