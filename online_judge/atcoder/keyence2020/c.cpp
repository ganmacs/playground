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
#include <numeric>

using namespace std;

int main()
{
  int N, K, S;

  cin >> N >> K >> S;

  for (int i = 0; i < K; i++) {
    cout << S << " ";
  }
  if (S == 1) {
    S++;
  } else {
    S--;
  }

  for (int i = 0; i < (N-K); i++) {
    cout << S << " ";
  }
  puts("");

  return 0;
}
