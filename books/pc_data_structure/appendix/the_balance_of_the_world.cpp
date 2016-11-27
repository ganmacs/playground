#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <stack>

using namespace std;
int n;

bool is_balance(string l)
{
  stack<char> s;
  for (int i = 0; i < (int)l.size(); i++) {
    if (l[i] == '[') {
      s.push(']');
    } else if (l[i] == ']') {
      if (s.size() <= 0 || s.top() != l[i]) {
        return false;
      } else {
        s.pop();
      }
    } else if (l[i] == '(') {
      s.push(')');
    } else if (l[i] == ')') {
      if (s.size() <= 0 || s.top() != l[i]) {
        return false;
      } else {
        s.pop();
      }
    }
  }

  return (s.size() == 0);
}

int main(){
  string l;
  while (getline(cin, l) && l != ".") {
    if(is_balance(l)) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}
