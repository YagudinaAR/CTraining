#include <iostream>
#include <cstring>
#include <algorithm>


using namespace std;

void swapLetters( int count, char* arr[])
{
	int value = 0;
	int sum = 0;
	int arrsize[10] = { 0 };
	char sub[15] = { 0 };
	string str;
	for (int i = 1; i < count - 1; i++)
	{
		int size = *(&arr[i] + 1) - arr[i] - 1;
		arrsize[i - 1] = size;
		sum += size;
		str += arr[i];
	}
	if (isdigit(*arr[count - 1]))
	{
		value = atoi(arr[count - 1]);
		for (int i = 0; i < sum; i++)
		{
			if (i + value >= sum)
				break;
			else swap(str[i], str[i + value]);
		}
		int k = 0;
		for (int i = 1; i < count - 1; i++)
		{
			int tmp = arrsize[i - 1];

			if (i - 1 > 0)
				k += arrsize[i - 2];

			for (int j = 0; j < tmp; j++)
			{
				sub[j] = str[k + j];

			}
			strncpy(arr[i], sub, arrsize[i - 1]);
			sub[0] = { 0 };
		}
	}
	for (int i = 1; i < count - 1; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	swapLetters(argc, argv);
	return 0;
 }
