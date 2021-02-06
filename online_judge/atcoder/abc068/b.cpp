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

  int a = 0, v = 0;
  cin >> a;
  for (int i = 6; i >= 0; i--) {
    if (((a >> i) & 1) == 1) {
      printf("%d\n", 1 << i);
      return 0;
    }
  }
  return 0;
}
