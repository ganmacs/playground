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
  int a, b;
  cin >> a >> b;
  if (b / 100 > 0) {
    a *= 1000;
  } else if (b / 10 > 0) {
    a *= 100;
  } else {
    a *= 10;
  }

  int v = a + b;
  int k = sqrt(v);
  if (k*k == v) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  return 0;
}
