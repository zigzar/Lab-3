#include <iostream>

using namespace std;


template <size_t N>
void fillSnake(int (&A)[N][N], int count) {
	for (int j = 0; j < N;)
	{
		for (int i = 0; i < N; i++)
		{
			A[i][j] = count++;
		}
		j++;
		if (j == N) break;
		for (int i = N - 1; i >= 0; i--)
		{
			A[i][j] = count++;
		}
		j++;
		if (j == N) break;
	};
};

template <size_t N>
void fillRight(int (&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curCol++) {
		A[curRow][curCol] = count++;
	}
	curCol--;
	curRow++;
}

template <size_t N>
void fillDown(int(&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curRow++) {
		A[curRow][curCol] = count++;
	}
	curCol--;
	curRow--;
}

template <size_t N>
void fillLeft(int(&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curCol--) {
		A[curRow][curCol] = count++;
	}
	curCol++;
	curRow--;
}

template <size_t N>
void fillUp(int(&A)[N][N], int length, int &curRow, int &curCol, int &count) {
	for (int i = 0; i < length; i++, curRow--) {
		A[curRow][curCol] = count++;
		//curRow--;
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

template <size_t N>
void coutMatrix(int(&A)[N][N]) {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j] << "\t";
			if (j == N - 1)
			{
				cout << endl;
			}
		}
	}
}

int main()
{
	setlocale(0, "");
	const int N = 11;
	int matrix[N][N] = { 0 };
	//fillSnake(matrix, 1);
	fillSpiral(matrix, 1);
	coutMatrix(matrix);

	short B[N][N];

}
