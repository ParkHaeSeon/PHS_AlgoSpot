#include <iostream>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include <algorithm>
#include <map>

using namespace std;

#define INF 987654321

int cache[10002] = { 0, };

string s;

// ���� �κа� �� �κ��� ���ڿ��� ���� ���̵� �Ǵ�
int classify(int Start, int End)
{
	string part = s.substr(Start, End - Start + 1);

	// ���̵� 1 = ��� ���ڰ� ���� ��
	if (part == string(part.size(), part[0])) return 1;

	// ���̵� 5 = ���ڰ� ���� ������ �̷� ��
	bool progressive = true;

	for (int i = 0; i < part.size() - 1; i++)
	{
		if (part[i + 1] - part[i] != part[1] - part[0])
		{
			progressive = false;
			break;
		}
	}

	// ���̵� 2 = ���ڰ� 1�� ���� �����ϰų� ���� ������ ��, �������� 1, -1
	if (progressive && abs(part[1] - part[0]) == 1) return 2;
	
	// ���̵� 4 = 2���� ���ڰ� ������ ���� ������ ��
	bool onlytwo = true;
	
	for (int i = 0; i < part.size(); i++)
	{
		if (part[i] != part[i % 2])
		{
			onlytwo = false;
			break;
		}
	}

	// ���̵� 4
	if (onlytwo) return 4;

	// ���̰� 5
	if (progressive) return 5;

	// ���̵� 10
	return 10;
}

int memorize(int Begin)
{
	// ���� ��� : ������ ���� �������� ���
	if (Begin == s.length()) return 0;

	int & ret = cache[Begin];

	if (ret != INF) return ret;

	for (int L = 3; L <= 5; L++)
	{
		if (Begin + L > s.length()) continue;

		ret = min(ret, memorize(Begin + L) + classify(Begin, Begin + L - 1));
	}

	return ret;
}

int main(void)
{
	int T = 0;

	scanf("%d", &T);

	while (T--)
	{
		fill(cache, cache + 10002, INF);

		cin >> s;

		printf("%d\n", memorize(0));
	}

	return 0;
}