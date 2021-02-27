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

  long long int X;
  cin >> X;

  cout << (((X + 100) - (X % 100)) - X) << endl;

  return 0;
}
