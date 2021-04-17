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
  unsigned long long N, A, B;
  cin >> N >> A >> B;

  if ((B-A) % 2 == 0) {
    cout << (B-A)/2 << endl;
    return 0;
  }

  unsigned long long ans1 = (A-1) + 1 + (B-A-1)/2;
  unsigned long long ans2 = (N-B) + 1 + (B-A-1)/2;
  cout << min(ans2, ans1) << endl;
  return 0;
}
