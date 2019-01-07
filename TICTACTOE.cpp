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

//turn�� �� ���� ��������� ��ȯ
bool isFinished(char turn)
{
	// ����
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] != turn) break;

			if (j == 2) return true;
		}
	}

	// ����
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (board[i][j] != turn) break;

			if (i == 2) return true;
		}
	}

	// ������ �Ʒ� �밢��
	for (int i = 0; i < 3; i++)
	{
		if (board[i][i] != turn) break;

		if (i == 2) return true;
	}

	// ���� �Ʒ� �밢��
	for (int i = 0; i < 3; i++)
	{
		if (board[i][2 - i] != turn) break;

		if (i == 2) return true;
	}

	return false;
}

// ƽ���� ������ �־��� ��, [0, 19682] ������ ������ ��ȯ�Ѵ�.
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

// �̹� ���� ���� �̱� �� ������ 1��, ��� �� ������ 0��, ���� -1�� �����Ѵ�.
int canWin(char turn)
{
	// ���� ��� : ������ ��밡 �ּ� �� ���� ������� ��� = ���� ���� ���
	if (isFinished('o' + 'x' - turn)) return -1;

	int result = cache[bijection()];

	// ��� ��ȯ ���� min�� ������.
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

	// �÷��� �� �� ���ų�, ��� �ص� ���� ���� �ּ��� ���
	if (minValue == 2) return result = 0;

	// �ּ��� ��밡 �̱�� �Ŷ�� �� ������ ����, ��밡 ���� �Ŷ�� �� �̱��.
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

		if (get == -1) // ��밡 �̱�� ���
		{
			printf("%c\n", 'x' + 'o' - start);
		}
		else if (get == 0) // ���º�
		{
			printf("TIE\n");
		}
		else if (get == 1) // ������ �̱�� ���
		{
			printf("%c\n", start);
		}
	}

	return 0;
}