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
#include <iomanip>

using namespace std;

unsigned long long int n1 = pow(10, 3);
unsigned long long int n2 = pow(10, 6);
unsigned long long int n3 = pow(10, 9);
unsigned long long int n4 = pow(10, 12);
unsigned long long int n5 = pow(10, 15);

unsigned long long int n11 = n2-n1;
unsigned long long int n12 = (n3-n2)*2;
unsigned long long int n13 = (n4-n3)*3;
unsigned long long int n14 = (n5-n4)*4;

int main()
{
  unsigned long long int N;
  cin >> N;

  // 10^3 - 10^5 = 1
  // 10^6 - 10^8 = 2
  // 10^9 - 10^11 = 3
  // 10^12 - 10^14 = 4
  // 10^15  = 5

  cout << std::setprecision(30);

  if (n1 > N) {
    cout << 0 << endl;
  } else if (n2 > N) {          // 10^6
    cout << (N-n1+1) << endl;
  } else if (n3 > N) {          // 10^9
    cout << (n11 + (N-n2+1)*2) << endl;
  } else if (n4 > N) {
    cout << (n11 + n12 + (N-n3+1)*3) << endl;
  } else if (n5 > N) {
    cout << (n11 + n12 + n13 + (N-n4+1)*4) << endl;
  } else {
    cout << (n11 + n12 + n13 + n14 + 5) << endl;
  }

  return 0;
}
