#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int n;
int RET[50];

int main()
{
  cin >> n;
  for (int i = 0; i < n + 1; i++) RET[i] = -1;
  RET[0] = 1;
  RET[1] = 1;
  for (int i = 2; i < n + 1; i++) RET[i] = RET[i-2] + RET[i-1];
  cout << RET[n] << endl;
  return 0;
}
