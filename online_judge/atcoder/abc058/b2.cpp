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

int main()
{
  string O, E;
  cin >> O >> E;

  for (int i = 0; i < E.size(); i++) {
    cout << O[i] << E[i];
  }

  if (O.size() != E.size()) {
    cout << O[O.size()-1];
  }
  puts("");

  return 0;
}
