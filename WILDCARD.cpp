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

string W, S;

int cache[102][102] = { 0, };

// ���ϵ�ī�� ���� W[w...]�� ���ڿ� S[s...]�� �����Ǵ��� ���θ� ��ȯ�Ѵ�.
int matchMemoized(int w, int s)
{
	// �޸������̼�
	int & ret = cache[w][s];

	if (ret != -1) return ret;

	// w�� s�� 1�� �����ϰ� ����ϴ� ��ſ� ���ϰ� ���ڿ��� ù �� ���ھ��� ��� �̵��� ���� �����Ǵ��� ���ȣ��� Ȯ��
	if (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) return ret = matchMemoized(w + 1, s + 1);

	// 2. ���� ���� �����ؼ� ���� ��� : ���ڿ��� ������� ��.
	if (w == W.size()) return ret = (s == S.size());

	// 4. *�� ������ ���� ��� : *�� �ƹ� ���ڵ� ������Ű�� ���� ������, �ƴϸ� �� ���ڸ� �� ������ų ������
	if (W[w] == '*')
	{
		if (matchMemoized(w + 1, s) || (s < S.size() && matchMemoized(w, s + 1))) return ret = 1;
	}

	// 3. �� ���� ��쿡�� ��� �������� �ʴ´�.
	return ret = 0;
}

int main(void)
{
	int N = 0, T = 0;

	vector<string> v;

	scanf("%d", &T);

	while (T--)
	{
		v.clear();

		cin >> W; // ���ϵ� ī�� ���ڿ�

		scanf("%d", &N);

		for (int i = 0; i < N; i++)
		{
			fill(&cache[0][0], &cache[101][102], -1);

			cin >> S; // ���ڿ� �Է�

			if (matchMemoized(0, 0) == 1) v.push_back(S);
		}

		sort(v.begin(), v.end());

		for (auto i : v) cout << i << '\n';
	}

	return 0;
}