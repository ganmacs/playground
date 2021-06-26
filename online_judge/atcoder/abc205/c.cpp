#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <array>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

void v(long long i,  long long j) {
  if (i == j) {
    puts("=");
  } else if (i > j) {
    puts(">");
  } else {
    puts("<");
  }
}

int main()
{
  long long A, B, C;
  cin >> A >> B >> C;

  if (C % 2 == 0) {
    v(abs(A), abs(B));
  } else {
    v(A, B);
  }

  return 0;
}
