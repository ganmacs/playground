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

int A[1000];

int main(int argc, char *argv[])
{

  int N;
  bool ok = true;
  cin >> N;


  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  for (int i = 0; i < N; i++) {
    if (A[i]%2 == 0) {
      if ((A[i]%3 == 0)||(A[i]%5 == 0)) {
      } else {
        ok = false;
      }
    }
  }

  cout << (ok ? "APPROVED" : "DENIED") << endl;

  return 0;
}
