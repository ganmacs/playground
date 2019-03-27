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
  long long p = 1;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    if (p > 1000000007) p %= 1000000007;
    p *= i;
  }

  p %= 1000000007;
  cout << p << endl;
}
