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
  long long K, A, B;
  cin >> K >> A >> B;

  long long a = 0;
  long long rest = K - A + 1;
  if (rest < 0) {
    a = 0;
  } else if (rest % 2 == 1) {
    a += A + 1 + (B-A)*(rest / 2);
  } else {
    a += A + (B-A)*(rest / 2);
  }

  cout << max(K + 1, a) << endl;

  return 0;
}
