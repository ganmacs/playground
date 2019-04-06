#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
  int a[5];
  for (int i = 0; i < 5; i++) {
    cin >> a[i];
  }

  long long v = 1e9;
  do {
    long long k = 0;
    for (int i = 0; i < 4; i++) {
      k += a[i];
      if (k%10 != 0) {
        k += (10-(k%10));
      }
    }
    k += a[4];

    v = min(v, k);
  } while (std::next_permutation(a, a + 5));

  cout << v << endl;
}
