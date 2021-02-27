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

int A[27];

int main(int argc, char *argv[])
{
  string w;
  cin >> w;

  for (int i = 0; i < 27; i++) {
    A[i] = 0;
  }

  for (int i = 0; i < w.length(); i++) {
    A[w[i]-'a']++;
  }


  for (int i = 0; i < 27; i++) {
    if (A[i] % 2 == 1) {
      cout << "No" << endl;
      return 0;
    }
  }

  cout << "Yes" << endl;


  return 0;
}
