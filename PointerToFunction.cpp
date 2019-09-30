#include <iostream>
using namespace std;

bool isMin(int a, int b)
{
	return a < b;
}
bool isMax(int a, int b)
{
	return a > b;
}
void selSort(int arr[], int size, bool(*isEqual)(int, int))
{
	int index = 0;
	for (int i = 0; i < size - 1; i++)
	{
		index = i;
		for (int j = i + 1; j < size; j++)
		{
			if (!((*isEqual)(arr[index], arr[j])))
				index = j;
		}
		if (index != i)
			swap(arr[i], arr[index]);
	}
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void bubbleSort(int arr[], int size, bool(*isEqual)(int, int))
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (!((*isEqual)(arr[j], arr[j + 1])))
				swap(arr[j], arr[j + 1]);
		}
	}
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void sortArr(void(*TypeSort)(int*, int, bool(*isEqual)(int, int)))
{
	int d[] = { 1,15,-44,3,-88,7 };
	if (TypeSort == selSort)
	{
		selSort(d, 6, &isMax);
		selSort(d, 6, &isMin);
	}

	if (TypeSort == bubbleSort)
	{
		bubbleSort(d, 6, &isMax);
		bubbleSort(d, 6, &isMin);
	}
}
int main()
{
	sortArr(&selSort);
	sortArr(&bubbleSort);
	return 0;
}