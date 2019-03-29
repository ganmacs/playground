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
  int N;
  int a = 0, b = 0;
  cin >> N;
  int v[1000];

  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }

  sort(v, v + N, greater<int>());

  for (int i = 0; i < N; i++) {
    if (a < b) {
      a += v[i];
    } else {
      b += v[i];
    }
  }

  cout << max(a, b) << endl;
}
