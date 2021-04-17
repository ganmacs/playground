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


unsigned long long cc(int n, int r){
  unsigned long long num = 1;
  for (int i = 1; i <= r; i++) {
    num = num * (n - i + 1) / i;
  }
  return num;
}

int main()
{
  int N, P;
  unsigned long long n1 = 0, n2 = 0;
  cin >> N >> P;
  vector<int> A(N);
  for (auto& vi: A) {
    cin >> vi;
    vi = (vi % 2);
    if (vi == 0) {
      n1++;
    } else {
      n2++;
    }
  };

  if (n2 == 0 && P == 1) {
    cout << 0 << endl;
    return 0;
  }

  unsigned long long v2 = pow(2, n1);
  unsigned long long v3 = 0;

  if (P == 0) {
    for (int i = 0; i <= n2; i += 2) {
      v3 += cc(n2, i);
    }
  } else {
    unsigned long long v3 = 0;
    for (int i = 1; i <= n2; i += 2) {
      v3 += cc(n2, i);
    }
  }

  cout << v2*v3 << endl;
  return 0;
}
