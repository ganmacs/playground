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
  long long N, A, B;
  cin >> N >> A >> B;

  if (B < A || (N == 1 && A != B)) {
    cout << 0 << endl;
  } else if (N == 1 && A == B) {
    cout << 1 << endl;
  } else {
    cout << (A+(B*(N-1))) - (A*(N-1)+B) + 1 << endl;
  }

  return 0;
}
