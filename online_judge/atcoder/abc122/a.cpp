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
  string s;

  cin >> s;

  if (s == "T") {
    cout << "A" << endl;
  } else if (s == "A") {
    cout << "T" << endl;
  } else if (s == "C") {
    cout << "G" << endl;
  } else if (s == "G") {
    cout << "C" << endl;
  }

  return 0;
}
