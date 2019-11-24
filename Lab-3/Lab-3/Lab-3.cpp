#include <iostream>

using namespace std;

const int N = 7;

/*void fillSpiral(*arr, ) {

};*/

int main()
{
	setlocale(0, "");
	short A[N][N];
	for (int j = 0, count = 1; j < N;)
	{
		for (int i = 0; i < N; i++)
		{
			A[i][j] = count++;
		}
		j++;
		if (j == N) break;
		for (int i = N-1; i >= 0; i--)
		{
			A[i][j] = count++;
		}
		j++;
		if (j == N) break;
	};

	cout << "Заполнение змейкой:\n";
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << A[i][j] << "\t";
			if (j == N-1)
			{
				cout << endl;
			}
		}
	}

	short B[N][N];

}
