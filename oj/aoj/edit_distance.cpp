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
  string a, b;
  cin >> a >> b;
  int al = a.length();
  int bl = b.length();

  for (int i = 0; i <= al; i++) d[i][0] = i;
  for (int i = 0; i <= bl; i++) d[0][i] = i;

  for (int i = 1; i <= al; i++) {
    for (int j = 1; j <= bl; j++) {
      int c = (a[i-1] == b[j-1]) ? 0 : 1;
      d[i][j] = min(d[i][j-1] + 1, min(d[i-1][j] + 1, d[i-1][j-1] + c));
    }
  }
  cout << d[al][bl] << endl;
}
