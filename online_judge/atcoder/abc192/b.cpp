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

  string S;
  cin >> S;


  for (int i = 0; i < S.length(); i++) {
    if (i % 2 == 0) {
      if (S[i] <= 'z' && S[i] >= 'a') {
      } else {
        cout << "No" << endl;
        return 0;
      }
    } else {
      if (S[i] <= 'Z' && S[i] >= 'A') {
      } else {
        cout << "No" << endl;
        return 0;
      }
    }
  }

  cout << "Yes" << endl;
  return 0;
}
