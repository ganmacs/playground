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
  string S;
  std::set<char> se;

  cin >> S;

  for (int i = 0; i < S.length(); i++) {
    auto it = se.find(S[i]);
    if (it != se.end()) {
      cout << "no" << endl;
      return 0;
    } else {
      se.insert(S[i]);
    }
  }

  cout << "yes" << endl;
  return 0;
}
