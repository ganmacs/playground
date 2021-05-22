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
#include <numeric>

using namespace std;

int main()
{
  long long sum = 0, N, a;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a;
    sum += (a-1);
  }

  cout << sum << endl;
  return 0;
}
