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
  string A, B;
  cin >> A >> B;

  if (A.length() > B.length()) {
    cout << "GREATER" << endl;
    return 0;
  } else if (A.length() < B.length()) {
    cout << "LESS" << endl;
    return 0;
  } else if (A == B) {
    cout << "EQUAL" << endl;
    return 0;
  }

  for (int i = 0; i < A.length(); i++) {
    if ((A[i]-'0') > (B[i]-'0')) {
      cout << "GREATER" << endl;
      return 0;
    } else {
      cout << "LESS" << endl;
      return 0;
    }
  }

  return 0;
}
