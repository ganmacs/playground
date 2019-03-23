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

string S;

long long cal(int l, int prev) {
  if (l >= S.size()) return 0;

  long long int v = 0;
  for (int i = 1; i <= l; i++) {
    long long vv = atoi(S.substr(0, i).c_str());
    if (i != l) {
      vv += atoi(S.substr(i, l).c_str());
    }
    v += cal(l + 1, prev + vv);
  }
  return v;
}

int main(int argc, char *argv[])
{
  cin >> S;
  int s = atoi(S.c_str());
  int len = S.size();
  long long int v = 0;

  v = cal(1, 0);
  return 0;
}
