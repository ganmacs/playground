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

const int INF = 10000000;

int main(int argc, char *argv[])
{
  int A, B, C;
  cin >> A >> B >> C;

  if (A <= B) {
    if (A <= C && C <= B) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  } else {
    if (B <= C && C <= A) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }

  return 0;
}
