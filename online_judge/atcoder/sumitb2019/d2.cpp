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
  int N;
  string S;
  set<string> s3, s2, s1;
  cin >> N >> S;
  string aaa = "xxx";
  for (int i = 0; i < N-2; i++) {
    aaa[0] = S[i];
    if (s1.find(aaa) != s1.end()) {
      continue;
    }
    s1.insert(aaa);

    for (int j = i + 1; j < N-1; j++) {
      aaa[1] = S[j];
      if (s2.find(aaa) != s2.end()) {
        continue;
      }
      s2.insert(aaa);

      for (int k = j + 1; k < N; k++) {
        aaa[2] = S[k];
        s3.insert(aaa);
      }
    }
  }

  cout << s3.size() << endl;

  return 0;
}
