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

int R, G, B, N;
long long ans = 0;

int main(int argc, char *argv[])
{
  cin >> R >> G >> B >> N;

  for (int i = 0; R*i <=  N; i++) {
    if (R*i > N) continue;
    for (int j = 0; R*i + G*j <= N; j++) {
      if ((N - (R*i + G*j)) % B == 0)  ans++;
    }
  }

  cout << ans << endl;
  return 0;
}
