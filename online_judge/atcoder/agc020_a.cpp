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
  int N, a, b;
  cin >> N >> a >> b;
  cout << (abs(b-a)%2 == 0 ? "Alice" : "Borys") << endl;
}
