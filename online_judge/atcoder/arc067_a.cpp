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

bool is_prime(int v) {
  for (int i = 2; i*i <=  v; i++) {
    if (v % i == 0) {
      return false;
    }
  }
  return true;
}


int main(int argc, char *argv[])
{
  int N;
  long long ans = 1, n = 1;
  cin >> N;

  for (int i = 2; i <= N; i++) {
    n = n * i
  }

  puts("\n===================================== start print");
  printf("%d\n", n);
  printf("%d\n", n % 5);
  puts("===================================== finish print\n");
  return 0;


  for (int i = 2; i <= N; i++) {
    if (is_prime(i)) {
      long long int r = 1;
      long long int j = n;
      while (j > 0) {
        puts("\n===================================== start print");
        printf("%d %d  %d\n", j % i, j, i);
        puts("===================================== finish print\n");
        if(j % i != 0) break;
        r++;
        j /= i;
      }
      printf("%lld %d\n", ans, r);
      ans = ans * r % 1000000007;
    }
  }

  cout << ans << endl;
  return 0;
}
