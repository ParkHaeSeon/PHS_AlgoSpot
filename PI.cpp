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

// 시작 부분과 끝 부분의 문자열에 대한 난이도 판단
int classify(int Start, int End)
{
	string part = s.substr(Start, End - Start + 1);

	// 난이도 1 = 모든 숫자가 같을 때
	if (part == string(part.size(), part[0])) return 1;

	// 난이도 5 = 숫자가 등차 수열을 이룰 때
	bool progressive = true;

	for (int i = 0; i < part.size() - 1; i++)
	{
		if (part[i + 1] - part[i] != part[1] - part[0])
		{
			progressive = false;
			break;
		}
	}

	// 난이도 2 = 숫자가 1씩 단조 증가하거나 단조 감소할 때, 등차수열 1, -1
	if (progressive && abs(part[1] - part[0]) == 1) return 2;
	
	// 난이도 4 = 2개의 숫자가 번갈아 가며 출현할 때
	bool onlytwo = true;
	
	for (int i = 0; i < part.size(); i++)
	{
		if (part[i] != part[i % 2])
		{
			onlytwo = false;
			break;
		}
	}

	// 난이도 4
	if (onlytwo) return 4;

	// 난이고 5
	if (progressive) return 5;

	// 난이도 10
	return 10;
}

int memorize(int Begin)
{
	// 기저 사례 : 수열의 끝에 도달했을 경우
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