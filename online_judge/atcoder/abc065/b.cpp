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
  int N, a[123456];

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  int n = 0, inc = 0, ans = -1;
  for (int i = 0; i < 10000000; i++) {
    n = a[n]-1;
    inc++;
    if (n == 1){
      ans = inc;
      break;
    }
  }

  cout << ans << endl;
}
