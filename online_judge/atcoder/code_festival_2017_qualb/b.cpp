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

  int N, M, a;
  map<int, int> MA;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> a;
    MA[a]++;
  }

  cin >> M;

  for (int i = 0; i < M; i++) {
    cin >> a;
    MA[a]--;

    if (MA[a] < 0) {
      cout << "NO" << endl;
      return 0;
    }
  }

  cout << "YES" << endl;
  return 0;
}
