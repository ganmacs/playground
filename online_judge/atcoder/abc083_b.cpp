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
  int N, A, B, a = 0, ans = 0;
  int a0, a1, a2, a3, a4;
  cin >> N >> A >> B;

  for (int i = 1; i <= N; i++) {
    a0 = (i%10);
    a1 = ((i/10)%10);
    a2 = ((i/100)%10);
    a3 = ((i/1000)%10);
    a4 = ((i/10000)%10);

    a = a0 + a1 + a2 + a3 + a4;
    if (A <= a && a <= B) {
      ans += i;
    };
  }
  printf("%d\n", ans);
}
