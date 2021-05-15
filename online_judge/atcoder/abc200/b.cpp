#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

int main()
{
  unsigned long long N, K, aa = 0;
  cin >> N >> K;

  for (int i = 0; i < K; i++) {
    if (N % 200 == 0) {
      N /= 200;
    } else {
      N = stoull(to_string(N) + "200");
    }
  }

  cout << N << endl;
  return 0;
}
