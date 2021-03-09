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
  int N, a, r = 0;
  map<int, int> v;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> a;

    if (a < 400) {
      v[0]++;
    } else if (a < 800) {
      v[1]++;
    } else if (a < 1200) {
      v[2]++;
    } else if (a < 1600) {
      v[3]++;
    } else if (a < 2000) {
      v[4]++;
    } else if (a < 2400) {
      v[5]++;
    } else if (a < 2800) {
      v[6]++;
    } else if (a < 3200) {
      v[7]++;
    } else {
      r++;
    }
  }

  cout << max(1, (int)v.size()) << " " << ((int)v.size() + r) << endl;
  return 0;
}
