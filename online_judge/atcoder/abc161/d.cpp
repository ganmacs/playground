#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  int K;
  cin >> K;

  queue<long long> que;
  for (int i = 1; i <= 9; i++) que.push(i);

  long long ans = 0;
  for (int i = 0; i < K; i++) {
    ans = que.front();
    que.pop();

    for (int i = -1; i <= 1; i++) {
      int j = (ans % 10) + i;
      if (j <= 9 && j >= 0) que.push(ans*10 + j);
    }
  }

  cout << ans << endl;
  return 0;
}
