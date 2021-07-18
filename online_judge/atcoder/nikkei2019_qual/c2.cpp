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

int main()
{
  int N;
  long long bs = 0, a, b;
  vector<long long> V;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    bs -= b;
    V.push_back(a + b);
  }
  sort(V.begin(), V.end(), greater<long long>());

  for (int i = 0; i < N; i += 2) bs += V[i];


  printf("%lld\n", bs);
  return 0;
}
