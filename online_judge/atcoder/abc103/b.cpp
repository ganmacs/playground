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


// int A[100];
// int B[100];

int main(int argc, char *argv[])
{

  string S, T;
  cin >> S >> T;

  for (int i = 0; i < T.length(); i++) {
    S = S.substr(S.length()-1, 1) + S.substr(0, S.length()-1);

    // cout << S << endl;

    if (S == T) {
      cout << "Yes" << endl;
      return 0;
    }
  }


  // for (int i = 0; i < 27; i++) {
  //   A[i] = 0;
  //   B[i] = 0;
  // }

  // for (int i = 0; i < S.length(); i++) {
  //   A[S[i]-'a']++;
  //   B[T[i]-'a']++;
  // }

  // // for (int i = 0; i < 27; i++) {
  // //   printf("%d ", A[i]);
  // // }
  // // puts("");

  // // for (int i = 0; i < 27; i++) {
  // //   printf("%d ", B[i]);
  // // }
  // // puts("");

  // for (int i = 0; i < 27; i++) {
  //   if (A[i] != B[i]) {
  //     cout << "No" << endl;
  //     return 0;
  //   }
  // }

  cout << "No" << endl;
  return 0;
}
