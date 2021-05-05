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
  int N;
  cin >> N;
  int v = N/100;

  if (v*100 <= N && v*105 >= N) {
    cout << 1 << endl;
  } else {
    cout << 0 << endl;
  }

  return 0;
}
