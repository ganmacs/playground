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
  int n;
  std::map<int, bool> r;

  cin >> n;
  r[n] = true;
  for (int i = 2; i < 1000001; i++) {
    if (n%2 == 1) {
      n = (3*n) + 1;
    } else {
      n >>= 1;
    }

    auto search = r.find(n);
    if (search != r.end()) {
      cout << i << endl;
      break;

    } else {
      r[n] = true;
    }
  }

  return 0;
}
