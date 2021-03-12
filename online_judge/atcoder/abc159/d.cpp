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

int inp[212345];

int main(int argc, char *argv[])
{
  int N;
  map<int, int> m;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> inp[i];
    m[inp[i]]++;
  }

  unsigned long long l = 0;
  for (auto &mi: m) {
    if (mi.second >= 2) {
      for (int i = 1; i < mi.second; i++) {
        l += i;
      }
    }
  }

  for (int i = 0; i < N; i++) {
    if (m[inp[i]] >= 2) {
      cout << (l - (m[inp[i]]-1)) << endl;
    } else {
      cout << l << endl;
    }
  }

  return 0;
}
