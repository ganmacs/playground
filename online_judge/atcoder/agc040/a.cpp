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
  string s;
  cin >> s;
  N = s.length();
  vector<long long> V;

  for (int i = 0; i < N;) {
    int j = i;
    while (j < N && s[i] == s[j]) {
      j++;
    }

    V.push_back(j-i);
    i = j;
  }
  long long ans = 0;

  if (V.size() == 1) {
    ans = (V[0] + 1)*V[0]/2;
  } else if (s[0] == '<') {
    for (int i = 0; i < V.size()-1; i += 2) {
      ans += max(V[i], V[i+1]);
      ans += V[i]*(V[i]-1)/2;
      ans += V[i+1]*(V[i+1]-1)/2;
    }

    if (V.size() % 2 == 1) {
      ans += V[V.size()-1]*(V[V.size()-1] + 1)/2;
    }
  } else {                      // ><><
    ans += V[0]*(V[0]+1)/2;
    for (int i = 1; i < V.size()-1; i += 2) {
      ans += max(V[i], V[i + 1]);
      ans += V[i]*(V[i]-1)/2;
      ans += V[i+1]*(V[i+1]-1)/2;
    }

    if (V.size() % 2 == 0) {
      ans += V[V.size()-1]*(V[V.size()-1] + 1)/2;
    }
  }

  cout << ans << endl;
  return 0;
}
