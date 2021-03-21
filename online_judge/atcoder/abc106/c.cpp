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

unsigned long long int A = 5000000000000000;

int main()
{
  string S;
  unsigned long long int K;

  cin >> S;
  cin >> K;

  unsigned long long int a = 0;
  for (int i = 0; i < S.length(); i++) {
    if (S[i] == '1') {
      a++;
    } else {
      cout << S[i] << endl;
      break;
    }

    if (a == K) {
      cout << 1 << endl;
      break;
    }
  }

  return 0;
}
