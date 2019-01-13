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

int main(void)
{
	int T = 0, N = 0, num = 0;

	scanf("%d", &T);

	while (T--)
	{
		int result = -1;

		vector<int> v;

		scanf("%d", &N);

		for (int i = 0; i < N; i++)
		{
			scanf("%d", &num);

			v.push_back(num);
		}

		int dp[600] = { 0, };

		for (int i = 0; i < N; i++)
		{
			dp[i] = 1;

			for (int j = 0; j < i; j++)
			{
				if (v.at(i) > v.at(j) && dp[j] + 1 > dp[i])
				{
					dp[i] = dp[j] + 1;
				}
			}

			result = max(result, dp[i]);
		}

		printf("%d\n", result);
	}

	return 0;
}