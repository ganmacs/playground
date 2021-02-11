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
  int N, K;
  int x;
  int r;
  cin >> N >> K;

  for (int i = 0; i < N; i++) {
    cin >> x;
    r += (min(x, K-x)*2);
  }

  cout << r << endl;
  return 0;
}
