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

  long long int N, ans = 0;
  cin >> N;


  for (int i = 1; i <= N; i++) {
    if (to_string(i).length() % 2 == 1) {
      ans++;
    };
  }

  cout << ans << endl;
  return 0;
}
