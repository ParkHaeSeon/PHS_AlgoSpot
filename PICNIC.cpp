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

int n = 0, m = 0;

bool Friends[11][11] = { false, };

bool used[11] = { false, };
// used[i] = i번째 학생은 짝이 있는가? true or false

int bruteforce()
{
	// 남은 학생들 중 가장 빠른 번호의 학생을 찾는다.
	int now = -1;

	for (int i = 0; i < n; i++)
	{
		if (!used[i])
		{
			now = i;
			break;
		}
	}

	// 기저 사례 : 모든 학생이 짝을 찾았으면, 한 가지 방법을 찾았으니 종료한다.
	if (now == -1) return 1;

	int ret = 0;

	// 이 학생과 짝지을 학생을 결정한다.
	for (int i = now + 1; i < n; i++)
	{
		// Friends[now][i] Friends[i][now] 둘 중 하나만 조건문에 써도 된다.
		if (!used[i] && Friends[now][i] && Friends[i][now])
		{
			// used[now]를 안 해주는 이유는 어차피 28번 째 줄의 조건이 있기 때문이다.

			used[now] = used[i] = true;

			ret += bruteforce();

			used[now] = used[i] = false;
		}
	}

	return ret;
}

int main(void)
{
	int s = 0, e = 0, T = 0;

	scanf("%d", &T);

	while (T--)
	{
		memset(used, false, sizeof(used));
		memset(Friends, false, sizeof(Friends));

		scanf("%d %d", &n, &m);

		for (int i = 0; i < m; i++)
		{
			scanf("%d %d", &s, &e);

			Friends[s][e] = true;
			Friends[e][s] = true;
		}

		printf("%d\n", bruteforce());
	}

	return 0;
}