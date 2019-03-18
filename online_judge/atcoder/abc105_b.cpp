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

const int MAX = 100000;

long long int A[300];

int main(int argc, char *argv[])
{
  int N, ans = 0;
  cin >> N;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if ((4*i + 7*j) == N) {
        puts("Yes");
        return 0;
      } else if ((4*i + 7*j) > N) {
        break;
      }
    }
  }

  puts("No");
}
