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
// used[i] = i��° �л��� ¦�� �ִ°�? true or false

int bruteforce()
{
	// ���� �л��� �� ���� ���� ��ȣ�� �л��� ã�´�.
	int now = -1;

	for (int i = 0; i < n; i++)
	{
		if (!used[i])
		{
			now = i;
			break;
		}
	}

	// ���� ��� : ��� �л��� ¦�� ã������, �� ���� ����� ã������ �����Ѵ�.
	if (now == -1) return 1;

	int ret = 0;

	// �� �л��� ¦���� �л��� �����Ѵ�.
	for (int i = now + 1; i < n; i++)
	{
		// Friends[now][i] Friends[i][now] �� �� �ϳ��� ���ǹ��� �ᵵ �ȴ�.
		if (!used[i] && Friends[now][i] && Friends[i][now])
		{
			// used[now]�� �� ���ִ� ������ ������ 28�� ° ���� ������ �ֱ� �����̴�.

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