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
  int N, a[1234567];
  cin >> N;

  a[0] = a[1] = 0;
  a[2] = 1;

  for (int i = 3; i < N; i++) {
    a[i] = (a[i-1] + a[i-2] + a[i-3]) % 10007;
  }

  cout << a[N-1] << endl;
  return 0;
}
