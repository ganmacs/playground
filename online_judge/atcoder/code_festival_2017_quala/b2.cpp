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
  int N, M, K;
  cin >> N >> M >> K;

  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= M; j++) {
      if (j*(N-i) + i*(M-j) == K) {
        cout << "Yes" << endl;
        return 0;
      }
    }
  }

  cout << "No" << endl;
  return 0;
}
