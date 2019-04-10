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
  long long N;
  cin >> N;
  string s = "0123456";

  int v = N % 30;
  for (int i = 0; i < v; i++) {
    swap(s[i%5 + 1], s[i%5 + 2]);
  }

  cout << s.substr(1, 6) << endl;
  return 0;
}
