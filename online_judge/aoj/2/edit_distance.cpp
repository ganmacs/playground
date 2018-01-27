#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;
static const int MAX = 1000;

string a, b;
int dp[MAX + 1][MAX + 1];

int edit_d()
{
  int al = a.length();
  int bl = b.length();

  for (int i = 0; i <= al; i++) dp[i][0] = i;
  for (int i = 0; i <= bl; i++) dp[0][i] = i;
  for (int i = 1; i <= al; i++) {
    for (int j = 1; j <= bl; j++) {
      int v = (a[i-1] == b[j-1]) ? 0 : 1;
      dp[i][j] = min(dp[i-1][j-1] + v, min(dp[i][j-1], dp[i-1][j]) + 1);
    }
  }

  return dp[al][bl];
}

int main()
{
  cin >> a >> b;
  cout << edit_d() << endl;
}
