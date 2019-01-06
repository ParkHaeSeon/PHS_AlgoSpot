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

// å 162p
const int coverType[4][3][2] = {
	{{0, 0}, {1, 0}, {0, 1}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {1, 0}, {1,-1}}
};

char Map[21][21];

int H = 0, W = 0;

bool visit[21][21] = { false, };

int backtracking()
{
	int h = -1, w = -1;

	bool stop = false;

	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			if (Map[i][j] == '#') continue;

			if (!visit[i][j])
			{
				h = i;
				w = j;

				stop = true;

				break;
			}
		}

		if (stop) break;
	}

	if (h == -1 && w == -1) return 1;

	int ret = 0;

	for (int a = 0; a < 4; a++)
	{
		int fy = h + coverType[a][0][0];
		int fx = w + coverType[a][0][1];
		
		int sy = h + coverType[a][1][0];
		int sx = w + coverType[a][1][1];				
		
		int ty = h + coverType[a][2][0];
		int tx = w + coverType[a][2][1];

		if (sy < 0 || sy >= H || sx < 0 || sx >= W || visit[sy][sx] || Map[sy][sx] == '#') continue;

		if (ty < 0 || ty >= H || tx < 0 || tx >= W || visit[ty][tx] || Map[ty][tx] == '#') continue;

		visit[fy][fx] = visit[sy][sx] = visit[ty][tx] = true;

		ret += backtracking();
	
		visit[fy][fx] = visit[sy][sx] = visit[ty][tx] = false;
	}
	
	return ret;
}

int main(void)
{
	int T = 0, emptyCount = 0;

	scanf("%d", &T);

	while (T--)
	{
		memset(visit, false, sizeof(visit));

		emptyCount = 0;

		scanf("%d %d", &H, &W);

		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				cin >> Map[i][j];

				if (Map[i][j] == '.') ++emptyCount;
			}
		}

		if (emptyCount % 3 != 0) printf("0\n");
		else printf("%d\n", backtracking());
	}
	
	return 0;
}