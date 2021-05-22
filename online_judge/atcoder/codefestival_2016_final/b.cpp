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

int main()
{
  long long N;
  cin >> N;
  long long i = N;
  for (; i >= 1; i--) {
    if (N > i*(i-1)/2) {
      N -= i;
      cout << i << endl;
    }
  }

  return 0;
}
