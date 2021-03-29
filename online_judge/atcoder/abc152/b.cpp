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
#include <numeric>

using namespace std;

int main()
{
  int a, b;
  string aa, bb;
  cin >> a >> b;

  for (int i = 0; i < b; i++) {
    aa += to_string(a);
  }

  for (int i = 0; i < a; i++) {
    bb += to_string(b);
  }



  if (aa < bb) {
    cout << aa << endl;
  } else {
    cout << bb << endl;
  }

  return 0;
}
