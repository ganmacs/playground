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
  int N, a[1000];
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  sort(a, a + N);
  cout << a[lower_bound(a, a + N-1, a[N-1])-a-1] << endl;
  return 0;
}
