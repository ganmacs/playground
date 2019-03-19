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
  int N, L;
  string a = "", s[200];
  cin >> N >> L;

  for (int i = 0; i < N; i++) cin >> s[i];

  sort(s, s + N);

  for (int i = 0; i < N; i++) {
    a += s[i];
  }

  printf("%s\n", a.c_str());
}
