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

  int N, a = 0, a2 = 0, a4 = 0, b;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> b;
    if (b % 4 == 0) {
      a4++;
    } else if (b % 2 == 0) {
      a2++;
    } else {
      a++;
    }
  }

  if ((a2 == 0 || a2 % 2 == 0) && a <= a4+1) {
    cout << "Yes" << endl;
  } else {
    cout << ((a <= a4) ? "Yes" : "No") << endl;
  }

  return 0;
}
