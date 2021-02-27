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

int main(int argc, char *argv[])
{

  long long int a, b;
  cin >> a >> b;

  if (a <= 0 && 0 <= b) {
    cout << "Zero" << endl;
  } else if (b < 0 && a < 0) {
    cout << (((abs(a - b) + 1) % 2 == 0) ? "Positive" : "Negative") << endl;
  } else {
    cout << "Positive" << endl;
  }

  return 0;
}
