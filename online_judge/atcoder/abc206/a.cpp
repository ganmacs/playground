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
  int N;
  cin >> N;
  int v = N * 1.08;

  if (v == 206) {
    puts("so-so");
  } else if (v < 206) {
    puts("Yay!");
  } else {
    puts(":(");
  }
  return 0;
}
