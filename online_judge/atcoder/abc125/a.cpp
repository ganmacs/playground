#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
  int A, B, T;

  cin >> A >> B >> T;
  int v = max((T/A)*B, 0);
  cout << v << endl;
  return 0;
}
