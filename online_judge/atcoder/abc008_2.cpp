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
  map<string, int> m;
  string s[60];
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> s[i];
    m[s[i]]++;
  }

  int maxv = 0;
  string a;
  for (auto v : m) {
    if (maxv < v.second) {
      maxv = v.second;
      a = v.first;
    }
  }

  cout << a.c_str() << endl;
  return 0;

}
