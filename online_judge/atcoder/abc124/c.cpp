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

int A[112345];
int B[112345];

int main(int argc, char *argv[])
{
  string S;
  cin >> S;

  for (int i = 0; i < S.length(); i++) {
    A[i] = i % 2;
    B[i] = (A[i] + 1) % 2;
  }

  auto a = 0, b = 0;

  for (int i = 0; i < S.length(); i++) {
    if (A[i] != (S[i] - '0')) {
      a++;
    }


    if (B[i] != (S[i] - '0')) {
      b++;
    }
  }

  cout << min(a, b) << endl;
  return 0;
}
