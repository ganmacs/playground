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
  int N, a, b;
  cin >> N;
  vector<pair<int, int>> V;

  for (int i = 0; i < N; i++) {
    cin >> a >> b;
    V.push_back(make_pair(a, b));
  }
  reverse(V.begin(), V.end());


  long long int c = 0;
  for (auto& vi: V) {
    long long t = c + vi.first;
    if (t % vi.second != 0) {
      c += vi.second - (t % vi.second);
    }
  };

  cout << c << endl;
  return 0;
}
