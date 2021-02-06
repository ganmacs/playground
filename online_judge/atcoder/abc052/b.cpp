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
  int x = 0, ans = 0, N;
  char c;

  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> c;
    if (c == 'I') {
      x++;
      ans = max(ans, x);
    } else {
      x--;
    }
  }

  cout << ans << endl;

  return 0;
}
