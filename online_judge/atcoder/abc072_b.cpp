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

const int MAX = 100000;


int main(int argc, char *argv[])
{
  string v;
  cin >> v;
  for (int i = 0; i < v.size(); i += 2) {
      cout << v[i];
  }
  puts("");
}
