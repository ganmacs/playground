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

const int LIMIT = 1e9 + 7;

int main()
{
  long long N, M;
  cin >> N >> M;

  if (N == M) {
    unsigned long long a = 1, b = 1;
    for (int i = 1; i <= M; i++) a = (a*i)%LIMIT;
    for (int i = 1; i <= N; i++) b = (b*i)%LIMIT;
    cout << ((((2*a)%LIMIT) * b) % LIMIT) << endl;
  } else if (abs(N-M) == 1) {
    unsigned long long a = 1, b = 1;
    for (int i = 1; i <= M; i++) a = (a*i)%LIMIT;
    for (int i = 1; i <= N; i++) b = (b*i)%LIMIT;
    cout << ((a * b) % LIMIT) << endl;
  } else {
    cout << 0 << endl;
  }

  return 0;
}
