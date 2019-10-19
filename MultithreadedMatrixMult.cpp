#include <iostream> 
#include <ctime>
#include <thread>
#include <mutex>

using namespace std;

const int NumberOfThreads = 4;

const int n = 500;

const int qSize = 250;

mutex mt;

int* matr_1 = new int[n * n];
int* matr_2 = new int[n * n];
int* matr_3 = new int[n * n];

void ThreadFunctionMult(int* a, int* b, int* c, int iSizeAbegin, int iSizeAend, int jSizeBbegin, int jSizeBend)
{
	mt.lock();
	for (int i = iSizeAbegin; i <= iSizeAend; ++i)
	{
		for (int j = jSizeBbegin; j <= jSizeBend; ++j)
		{
			for (int z = 0; z < n; ++z)
			{
				matr_3[i * n + j] += matr_1[i * n + z] * matr_2[z * n + j];

			}

		}
	}
	mt.unlock();
}

int main()
{
	srand(time(0));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matr_1[i*n+j] = rand() % 3;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matr_2[i * n + j] = rand() % 3;
		}
	}
	setlocale(LC_ALL, "rus");
	clock_t start, end;
	start = clock();
	thread thr[NumberOfThreads];
	thr[0] = thread(ThreadFunctionMult, matr_1, matr_2, matr_3, 0, qSize - 1, 0, qSize - 1);
	thr[0].join();
	thr[1] = thread(ThreadFunctionMult, matr_1, matr_2, matr_3, 0, qSize - 1, qSize, n - 1);
	thr[1].join();
	thr[2] = thread(ThreadFunctionMult, matr_1, matr_2, matr_3, qSize, n - 1, 0, qSize - 1);
	thr[2].join();
	thr[3] = thread(ThreadFunctionMult, matr_1, matr_2, matr_3, qSize, n - 1, qSize, n - 1);
	thr[3].join();
	end = clock() - start;
	cout << "Время выполнения программы: " << (end / (double)CLOCKS_PER_SEC) << endl;
	delete[] matr_1;
	delete[] matr_2;
	delete[] matr_3;
	return 0;
}