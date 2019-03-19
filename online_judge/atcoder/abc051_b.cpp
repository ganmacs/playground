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
  int K, S, ans = 0;
  cin >> K >> S;

  for (int i = 0; i <= K; i++) {
    if (i > S) break;

    for (int j = 0; j <= K; j++) {
      if (i + j > S) break;
      if (S <= (i + j + K)) ans++;
    }
  }

  printf("%d\n", ans);
}
