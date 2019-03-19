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
  int N, tmp = 0, v = 0;
  cin >> N;

  tmp = N;
  while (tmp > 0) {
    v += (tmp % 10);
    tmp /= 10;
  }

  if (N % v == 0) {
    puts("Yes");
  } else {
    puts("No");
  }
}
