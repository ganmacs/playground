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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  string O, E, S = "";
  cin >> O >> E;

  for (int i = 0; i < E.length(); i++) {
    S += O[i];
    S += E[i];
  }

  if (E.length() != O.length()) {
    S += O[O.length()-1];
  }
  cout << S << endl;
  return 0;
}
