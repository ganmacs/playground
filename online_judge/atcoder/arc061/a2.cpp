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
string S;
int len;

long long int dfs(int i, long long s1,  long long s) {
  if (i == len) {
    return s1 + s;
  }

  return dfs(i + 1, s1, s*10 + (S[i]-'0')) + dfs(i + 1, s1 + s, (S[i]-'0'));
}

int main(int argc, char *argv[])
{
  cin >> S;
  len = S.length();
  long long ans = 0;
  cout << dfs(1, 0, S[0]-'0') << endl;
  return 0;
}
