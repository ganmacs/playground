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
  int a, b;
  cin >> a >> b;
  if (a > b) {
    cout << min(a-b, (10 - a + b)) << endl;
  } else {
    cout << min(b-a, (10 - b + a)) << endl;
  }
}
