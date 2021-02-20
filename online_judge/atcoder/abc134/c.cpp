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

string S, T;
int len;
bool finish;

void dfs(int v) {
  if (len == v) {
    cout << S << endl;
    finish = true;
    return;
  }

  if (S[v] == '?') {
    for (int i = 0; i < 26; i++) {
      S[v] = 'a' + i;
      dfs(v + 1);
      S[v] = '?';
      if (finish) return;
    }
  } else {
    dfs(v + 1);
  }
}

int main(int argc, char *argv[])
{
  cin >> S;
  cin >> T;
  len = S.size();

  for (int i = len-T.size(); i >= 0 ;i--) {
    bool ok = false;
    for (int j = 0; j < T.size(); j++) {
      if (S[i + j] == T[j] || S[i + j] == '?') {
        ok = true;
      } else {
        ok = false;
        break;
      }
    }

    if (ok == true) {
      for (int j = 0; j < T.size() ; j++) {
        swap(S[i + j], T[j]);
      }
      dfs(0);
      return 0;
    }
  }

  cout << "UNRESTORABLE" << endl;
}
