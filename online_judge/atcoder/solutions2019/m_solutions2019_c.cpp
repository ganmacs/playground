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
  int N, A, B, C;
  // cin >> N >> A >> B >> C;

  float v = 0.0;
  for (int i = 0; i < 4; i++) {
    v += pow(0.5, i) + pow(0.5, 4-i);
  }

  cout << v << endl;


  return 0;
}
