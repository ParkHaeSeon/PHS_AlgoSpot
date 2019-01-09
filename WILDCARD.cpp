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

// 와일드카드 패턴 W[w...]가 문자열 S[s...]에 대응되는지 여부를 반환한다.
int matchMemoized(int w, int s)
{
	// 메모이제이션
	int & ret = cache[w][s];

	if (ret != -1) return ret;

	// w와 s를 1씩 증가하고 계속하는 대신에 패턴과 문자열의 첫 한 글자씩을 뗴고 이들이 서로 대응되는지 재귀호출로 확인
	if (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) return ret = matchMemoized(w + 1, s + 1);

	// 2. 패턴 끝에 도달해서 끝난 경우 : 문자열도 끝났어야 참.
	if (w == W.size()) return ret = (s == S.size());

	// 4. *를 만나서 끝난 경우 : *에 아무 글자도 대응시키지 않을 것인지, 아니면 한 글자를 더 대응시킬 것인지
	if (W[w] == '*')
	{
		if (matchMemoized(w + 1, s) || (s < S.size() && matchMemoized(w, s + 1))) return ret = 1;
	}

	// 3. 이 외의 경우에는 모두 대응되지 않는다.
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

		cin >> W; // 와일드 카드 문자열

		scanf("%d", &N);

		for (int i = 0; i < N; i++)
		{
			fill(&cache[0][0], &cache[101][102], -1);

			cin >> S; // 문자열 입력

			if (matchMemoized(0, 0) == 1) v.push_back(S);
		}

		sort(v.begin(), v.end());

		for (auto i : v) cout << i << '\n';
	}

	return 0;
}