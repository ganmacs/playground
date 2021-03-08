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

// int A[1000];

int main(int argc, char *argv[])
{
  string S;
  cin >> S;
  int a[4] = { 0, 0, 0, 0};

  for (int i = 0; i < S.length(); i++) {
    if (S[i] == 'S') {
      a[0]++;
    } else if (S[i] == 'W') {
      a[1]++;
    } else if (S[i] == 'E') {
      a[2]++;
    } else if (S[i] == 'N') {
      a[3]++;
    }
  }

  if (a[0] == 0 && a[3] != 0) {
    cout << "No" << endl;
  } else if (a[0] != 0 && a[3] == 0) {
    cout << "No" << endl;
  } else if (a[1] != 0 && a[2] == 0) {
    cout << "No" << endl;
  } else if (a[1] == 0 && a[2] != 0) {
    cout << "No" << endl;
  } else {
    cout << "Yes" << endl;
  }

  return 0;
}
