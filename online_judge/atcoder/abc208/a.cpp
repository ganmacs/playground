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

int main()
{
  long long A, B;
  cin >> A >> B;

  if (1*A <= B && B <= 6*A) {
    puts("Yes");
  } else {
    puts("No");
  }

  return 0;
}
