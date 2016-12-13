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
int n;

int d[1000 + 1][1000 + 1];
int main(){
  string s1, s2;
  cin >> s1 >> s2;
  int ss1 = s1.length();
  int ss2 = s2.length();

  for (int i = 0; i <= ss1; i++) d[i][0] = i;
  for (int i = 0; i <= ss2; i++) d[0][i] = i;

  for (int i = 1; i <= ss1; i++) {
    for (int j = 1; j <= ss2; j++) {
      int c = (s1[i-1] == s2[j-1]) ? 0 : 1;
      d[i][j] = min(d[i][j-1] + 1, min(d[i-1][j] + 1, d[i-1][j-1] + c));
    }
  }
  cout << d[ss1][ss2] << endl;
}
