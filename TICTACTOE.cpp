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

int cache[19683] = { 0, }; // 3^9

vector<string> board;

//turn이 한 줄을 만들었는지 반환
bool isFinished(char turn)
{
	// 가로
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != turn) break;

			if (j == 2) return true;
		}
	}

	// 세로
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][j] != turn) break;

			if (i == 2) return true;
		}
	}

	// 오른쪽 아래 대각선
	for (int i = 0; i < 3; i++)
	{
		if (board[i][i] != turn) break;

		if (i == 2) return true;
	}

	// 왼쪽 아래 대각선
	for (int i = 0; i < 3; i++)
	{
		if (board[i][2 - i] != turn) break;

		if (i == 2) return true;
	}

	return false;
}

// 틱택토 게임이 주어질 때, [0, 19682] 범위의 정수로 변환한다.
int bijection()
{
	int ret = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret *= 3;

			if (board[i][j] == 'o') ++ret;
			else if (board[i][j] == 'x') ret += 2;
		}
	}

	return ret;
}

// 이번 턴인 내가 이길 수 있으면 1을, 비길 수 있으면 0을, 지면 -1을 리턴한다.
int canWin(char turn)
{
	// 기저 사례 : 마지막 상대가 둬서 한 줄이 만들어진 경우 = 내가 지는 경우
	if (isFinished('o' + 'x' - turn)) return -1;

	int result = cache[bijection()];

	// 모든 반환 값의 min을 취하자.
	int minValue = 2;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == '.')
			{
				board[i][j] = turn;

				minValue = min(minValue, canWin('o' + 'x' - turn));

				board[i][j] = '.';
			}
		}
	}

	// 플레이 할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우
	if (minValue == 2) return result = 0;

	// 최선이 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다.
	return result = -minValue;
}

int main(void)
{
	int T = 0;

	scanf("%d", &T);

	while (T--)
	{
		string s;

		int who = 0;

		fill(cache, cache + 19683, -2);

		if (!board.empty()) board.clear();

		for (int i = 0; i < 3; i++)
		{
			cin >> s;

			for (int j = 0; j < s.length(); j++)
				if (s.at(j) != '.') ++who;

			board.push_back(s);
		}

		char start = 'x';

		if (who % 2 != 0) start = 'o';

		int get = canWin(start);

		if (get == -1) // 상대가 이기는 경우
		{
			printf("%c\n", 'x' + 'o' - start);
		}
		else if (get == 0) // 무승부
		{
			printf("TIE\n");
		}
		else if (get == 1) // 내가가 이기는 경우
		{
			printf("%c\n", start);
		}
	}

	return 0;
}