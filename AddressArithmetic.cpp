#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

template<typename T>
int getSize(T* first, T* last)
{
	int size = 1;
	while (first != last)
	{
		size++;
		first++;
	}
	return size;
}


bool isPalindrome(string str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	int j = str.size() - 1;
	int i = 0;
	while ((i < j))
	{
		if (str[i] != str[j]) return false;
		i++;
		j--;
	}
	return true;
}

string reverseWords(string str)
{
	int size = count(str.begin(), str.end(), ' ') + 1;
	char** p = new char* [size];
	char sub[50] = { 0 };
	int i = 0;
	int j = 0;
	int k = 0;
	while (str[j] != '\0')
	{
		if (size < i) break;
		if (str[j] != ' ')
		{
			sub[k] = str[j];
			k++;
		}
		if (str[j] == ' ' || (str[j + 1] == '\0'))
		{
			p[size - 1 - i] = new char[k + 1];
			strncpy(p[size - 1 - i], sub, k);
			i++;
			k = 0;
			sub[0] = { 0 };
		}

		j++;
	}
	string s;
	for (int i = 0; i < size; i++)
	{
		s += *(p + i);
		s += " ";
		delete[] p[i];
	}
	delete[] p;
	return s;
}

int main()
{
	string str = "буря мглою небо кроет";
	string str2 = "a roza upala na lapu azora";
	int sz = getSize(&str[0], &str[20]);
	int p[] = { 1,2,3,4,5,6 };
	int sz2 = getSize(&p[0], &p[5]);
	cout << sz << " " << sz2 << endl;
	string s = reverseWords(str);
	cout << s << endl;
	bool f1 = isPalindrome(str);
	bool f2 = isPalindrome(str2);
	cout << f1 << " " << f2 << endl;
	return 0;
}