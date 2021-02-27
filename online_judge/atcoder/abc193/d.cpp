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

long long int A[10];
int L[4], R[4];

long long int aaa(int kk[10]) {
  long long int ans = 0;

  for (int i = 1; i < 10; i++) {
    ans += (i * pow(10, kk[i]));
  }

  return ans;
}

int main(int argc, char *argv[])
{
  long long int K;
  string S, T;
  cin >> K >> S >> T;

  for (int i = 1; i < 10; i++) {
    A[i] = K;
  }

  for (int i = 0; i < S.length(); i++) {
    L[i] = S[i]-'0';
    A[S[i]-'0']--;
  }

  for (int i = 0; i < T.length(); i++) {
    R[i] = T[i]-'0';
    A[T[i]-'0']--;
  }

  long long int k = (K*10)-8;
  long long unsigned int all = k*(k-1);

  for (int i = 1; i < 10; i++) {
    if (A[i]) {
    }
  }


  return 0;
}
