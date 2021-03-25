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

int main()
{
  string s;
  stack<char> st, st2;
  cin >> s;

  for (int i = 0; i < s[i]; i++) {
    if (s[i] == 'B') {
      if (!st.empty()) {
        st.pop();
      }
    } else {
      st.push(s[i]);
    }
  }

  while (!st.empty()) {
    st2.push(st.top());
    st.pop();
  }

  while (!st2.empty()) {
    cout << st2.top();
    st2.pop();
  }
  puts("");

  return 0;
}
