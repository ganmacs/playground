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

int main(int argc, char *argv[])
{
  long long int N, K;

  cin >> N >> K;

  if (N < K) {
    auto k = abs(N-K);
    cout << min(N, k) << endl;
  } else {
    auto v = N / K;
    auto v1 = N - v*K;
    auto v2 = N - (v + 1)*K;
    cout << min(abs(v1), abs(v2)) << endl;
  }


  return 0;
}
