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

char Map[5][5];

char word[11];

int dy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dx[8] = { 0, -1, 1, -1, 1, -1, 1, 0 };

bool visit[5][5][11] = { false, };

bool bruteforce(int y, int x, int index)
{
	visit[y][x][index] = true; // 방문 기록

	if (Map[y][x] != word[index]) return false; // 일치하지 않으면 false

	if (index == strlen(word) - 1) return true;

	for (int i = 0; i < 8; i++)
	{
		int ny = y + dy[i];
		int nx = x + dx[i];

		if (ny < 0 || ny >= 5 || nx < 0 || nx >= 5 || visit[ny][nx][index + 1]) continue;

		if (bruteforce(ny, nx, index + 1)) return true;
	}

	return false;
}

int main(void)
{
	int T = 0;

	scanf("%d", &T);

	while (T--)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				cin >> Map[i][j];
			}
		}

		int N = 0;

		scanf("%d", &N);

		for (int i = 0; i < N; i++)
		{
			memset(visit, false, sizeof(visit));

			scanf("%s", word);

			printf("%s ", word);

			bool result = false;

			for (int h = 0; h < 5; h++)
			{
				for (int w = 0; w < 5; w++)
				{
					if (bruteforce(h, w, 0))
					{
						result = true;

						break;
					}
				}

				if (result) break;
			}

			if (result) printf("YES\n");
			else printf("NO\n");
		}
	}

	return 0;
}
