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
  int N;
  string S;
  cin >> N;
  cin >> S;
  int ans1 = 0, ans2 = 0;
  int i = 0;
  for (; i < N; i++) {
    if (S[i] == '#') break;
  }

  int j = N - 1;
  for (; j >= 0; j--) {
    if (S[j] == '.') break;
  }


  while (i <= j) {
    int a = 0, b = 0;
    for (; i <= j; i++) {
      if (S[i] == '.') {
        i--;
        break;
      } else {
        a++;
      }
    }

    for (; j >= i; j--) {
      if (S[j] == '#') {
        j--;
        break;
      } else {
        b++;
      }
    }

    if (i < j) {
      ans1 += a;
      ans1 += b;
    }
  }

  cout << ans1 << endl;
  return 0;
}
