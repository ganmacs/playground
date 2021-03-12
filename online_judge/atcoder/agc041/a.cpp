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
  unsigned long long N, A, B, nn;
  cin >> N >> A >> B;

  nn = N/2;

  if ((B-A) % 2 == 0) {
    cout << ((B-A)/2) << endl;
  } else {
    unsigned long long kk = 0;
    cout << (min(A-1, N-B)+1+(B-A-1)/2) << endl;
  }

  return 0;
}
