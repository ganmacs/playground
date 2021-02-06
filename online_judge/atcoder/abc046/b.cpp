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
  cin >> N >> K;
  long long v = K;

  for (int i = 1; i < N; i++) v *= (K-1);
  cout << v << endl;
}
