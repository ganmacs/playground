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

  long long unsigned int ll = 1, lc = 2, lr;
  int N;
  cin >> N;

  if (N == 1) {
    cout << 1 << endl;
    return 0;
  }


  for (int i = 1; i < N; i++) {
    lr = ll + lc;
    lc = ll;
    ll = lr;
  }

  cout << ll << endl;
  return 0;
}
