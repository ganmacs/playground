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
  int A, B;
  string S;

  cin >> A >> B;

  cin >> S;

  for (int i = 0; i < S.length(); i++) {
    if (A == i) {
      if (S[i] != '-') {
        cout << "No" << endl;
        return 0;
      }
    } else {
      if('0' > S[i] || S[i] > '9') {
        cout << "No" << endl;
        return 0;
      }
    }
  }

  cout << "Yes" << endl;
  return 0;
}
