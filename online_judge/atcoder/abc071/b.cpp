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
  int A[26];

  cin >> S;

  for (int i = 0; i < 26; i++) {
    A[i] = 0;
  }

  for (int i = 0; i < S.length(); i++) {
    A[S[i]-'a']++;
  }

  for (int i = 0; i < 26; i++) {
    if (A[i] == 0) {
      printf("%c\n", 'a' + i);
      return 0;
    }
  }

  cout << "None" << endl;
  return 0;
}
