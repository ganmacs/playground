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
  unsigned long long int N, A, B;
  cin >> N >> A >> B;

  if ((B - A) % 2 == 0) {
    cout << (B-A)/2 << endl;
  } else {
    cout << (min(A-1, N-B) + 1 + (B-A-1)/2)<< endl;;
  }

  return 0;
}
