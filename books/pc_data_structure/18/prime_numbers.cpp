#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;

static const int MAX = 10000000;

int n;
vector<int> P;

bool is_prime(int v)
{
  if (v < 2) return false;
  else if (v == 2) return true;

  if (v % 2 == 0) return false;

  for (int i = 3; i * i <=  v; i += 2) {
    if (v % i == 0) return false;
  }

  return true;
}

int main(){
  cin >> n;
  int v = 0, x;

  for (int i = 0; i < n; i++) {
    cin >> x;
    if (is_prime(x)) v++;
  }

  cout << v << endl;
}
