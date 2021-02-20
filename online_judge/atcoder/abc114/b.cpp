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

  string s;
  cin >> s;

  int ans = 1000;

  for (int i = 0; i < s.length()-2; i++) {
    int k = stoi(s.substr(i, 3));
    printf("%d\n", k);
    ans = min(abs(753-k), ans);
  }

  cout << ans << endl;

  return 0;
}
