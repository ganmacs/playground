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
#include <list>

using namespace std;

int main()
{
  string S;
  cin >> S;
  int a = 0, b = 0;

  for (auto& vi: S) {
    if (vi == '0') {
      a++;
    } else {
      b++;
    }
  }

  cout << (S.size() - abs(a-b)) << endl;
  return 0;
}
