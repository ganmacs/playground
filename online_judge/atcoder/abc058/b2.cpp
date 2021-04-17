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
  string A, B, s = "";
  cin >> A >> B;

  for (int i = 0; i < min(A.size(), B.size()); i++) {
    s += A[i];
    s += B[i];
  }

  if (A.size() != B.size()) {
    s += A[A.size()-1];
  }

  cout << s << endl;
  return 0;
}
