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

long long int H[112345], H2[112345];

int main(int argc, char *argv[])
{

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> H[i];
  }

  if (N == 1) {
    cout << "Yes" << endl;
    return 0;
  }

  bool f = false;
  for (int i = N-2; i >= 0; i--) {
    H2[i] = H[i+1]-H[i];

    if (H2[i] < -1) {
      cout << "No" << endl;
      return 0;
    }

    // cout << H2[i] << " ";
    if (H2[i] == -1) {
      H[i]--;
    }
  }
  // puts("");

  for (int i = 0; i < N-1; i++) {
    H2[i] = H[i+1]-H[i];

    if (H2[i] <= -1) {
      cout << "No" << endl;
      return 0;
    }
    // cout << H2[i] << " ";
  }
  // puts("");

  cout << "Yes" << endl;
  return 0;
}
