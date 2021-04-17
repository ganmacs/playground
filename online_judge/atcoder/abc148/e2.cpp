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
  unsigned long long N;
  cin >> N;

  if (N % 2 == 1) {
    cout << 0 << endl;
  } else {
    unsigned long long v = 0;

    while (N) {
      v += (N/(5*2));
      N /= 5;
    }
    cout << v << endl;
  }

  return 0;
}
