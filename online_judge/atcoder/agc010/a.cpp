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
  int N, v, a = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> v;
    if (v % 2 == 1) a++;
  }

  cout << (a % 2 == 1 ? "NO" : "YES") << endl;
  return 0;
}
