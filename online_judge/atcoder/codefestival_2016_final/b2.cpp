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
  for (long long i = N; i >= 0; i--) {
    if (i*(i-1)/2 < N) {
      cout << i << endl;
      N -= i;
    }
  }

  return 0;
}
