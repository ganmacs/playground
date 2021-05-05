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

int P[10] = {0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,1 ,2};
int Q[10] = {1 ,1 ,1 ,2 ,2 ,3 ,2 ,2 ,3 ,3};
int R[10] = {2 ,3 ,4 ,3 ,4 ,4 ,3 ,4 ,4 ,4};

int
main()
{
  int N;
  string s;
  cin >> N;
  unsigned long long m[5] = {0, 0, 0, 0, 0}, ans = 0;;
  unsigned long long ss = 0;
  for (int i = 0; i < N; i++) {
    cin >> s;
    if (s[0] == 'M') {
      m[0]++; ss++;
    } else if (s[0] == 'A') {
      m[1]++; ss++;
    } else if (s[0] == 'R') {
      m[2]++; ss++;
    } else if (s[0] == 'C') {
      m[3]++; ss++;
    } else if (s[0] == 'H') {
      m[4]++; ss++;
    }
  }

  for (int i = 0; i < 10; i++) {
    ans += m[P[i]]*m[Q[i]]*m[R[i]];
  }

  cout << ans << endl;
  return 0;
}
