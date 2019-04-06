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

int main(int argc, char *argv[])
{

  int a[5], k;
  for (int i = 0; i < 5; i++) {
    cin >> a[i];
  }
  cin >> k;

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (abs(a[i]-a[j]) > k) {
        cout << ":(" << endl;
        return 0;
      }
    }
  }

  cout << "Yay!" << endl;
 }
