#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>

using namespace std;

string getStr(string s)
{
	string str = s;
	reverse(str.begin(), str.end());
	return str;
}

bool is_ready(future<string> const& f)
{
	return f.wait_for(chrono::seconds(0)) == future_status::ready;
}

int main()
{
	string s = "everything is gonna be alright ";
	vector<future<string>> vec;
	int i = 0, k = 0;
	for (auto& it : s)
	{
		++k;
		if (s[i] == ' ')
		{
			string p = s.substr(i - k + 1, k);
			vec.push_back(async(launch::async, getStr, p));
			k = 0;
		}

		++i;
	}
	bool flag = true;
	int count = 0;
	while (flag)
	{	
		for (auto& it : vec)
		{
			if (is_ready(it))
			{
				cout << it.get() << endl;
				count++;
			}
		}
		if (count == vec.size()) flag = false;
	}

	while (!vec.empty())
		vec.pop_back();
	return 0;
}