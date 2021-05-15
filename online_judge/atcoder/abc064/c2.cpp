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
  map<int, int> M;
  int o = 0;

  int N, a;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> a;
    if (a < 400) {
      M[0]++;
    } else if (a < 800) {
      M[1]++;
    } else if (a < 1200) {
      M[2]++;
    } else if (a < 1600) {
      M[3]++;
    } else if (a < 2000) {
      M[4]++;
    } else if (a < 2400) {
      M[5]++;
    } else if (a < 2800) {
      M[6]++;
    } else if (a < 3200) {
      M[7]++;
    } else {
      o++;
    }
  }


  cout << max((int)M.size(), 1) << " " << (M.size() + o) << endl;
  return 0;
}
