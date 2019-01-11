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

int tri[110][110] = { 0, };

int main(void)
{
	int T = 0, n = 0, num = 0;

	scanf("%d", &T);

	while (T--)
	{
		memset(tri, 0, sizeof(tri));

		int MAX = 0;

		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= i; j++)
			{
				scanf("%d", &tri[i][j]);

				if (j == 1) tri[i][j] = tri[i - 1][j] + tri[i][j];
				else if (i == j) tri[i][j] = tri[i - 1][j - 1] + tri[i][j];
				else tri[i][j] = max(tri[i - 1][j], tri[i - 1][j - 1]) + tri[i][j];

				MAX = max(MAX, tri[i][j]);
			}
		}
		
		printf("%d\n", MAX);
	}

	return 0;
}