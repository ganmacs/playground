#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n;
int RET[50];

int fib(int i)
{
  if (RET[i] != -1) return RET[i];
  return RET[i] = fib(i-1) + fib(i-2);
}

int main()
{
  cin >> n;
  for (int i = 0; i < n + 1; i++) RET[i] = -1;
  RET[0] = 1;
  RET[1] = 1;
  cout << fib(n) << endl;
  return 0;
}
