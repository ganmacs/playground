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
  int A, B, v = 0, ans = 0;
  cin >> A >> B;

  for (int i = A; i <= B; i++) {
    int tmp[5], vv = i;
    for (int j = 0; j < 5; j++) {
      tmp[j] = vv % 10;
      vv /= 10;
    }

    if ((tmp[0] == tmp[4]) && (tmp[1] == tmp[3])) ans++;
  }
  printf("%d\n", ans);
}
