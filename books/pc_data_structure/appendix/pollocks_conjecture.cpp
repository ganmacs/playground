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
typedef pair<int,int> P;
static const int MAX = 1000000;

int all[MAX + 10];
int odd[MAX + 10];

int main(){
  int n;

  for (int i = 1; i <= MAX; i++) {
    odd[i] = all[i] = MAX;
  }

  for (int i = 1; ; i++) {
    int x = i * (i + 1) * (i + 2) / 6;
    if (x > MAX) break;

    for (int j = x; j <= MAX; j++) {
      all[j] = min(all[j], all[j - x] + 1);
    }

    if (x & 1) {
      for (int j = x; j <= MAX; j++) {
        odd[j] = min(odd[j], odd[j - x] + 1);
      }
    }
  }

  while (scanf("%d", &n), n) {
    printf("%d %d\n", all[n], odd[n]);
  }
}
