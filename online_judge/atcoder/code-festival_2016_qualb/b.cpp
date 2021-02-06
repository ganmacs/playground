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

int NN = 200;

int main(int argc, char *argv[])
{
  int N, A, B;
  string S;

  int a = 0, b = 0, ab = 0;

  cin >> N >> A >> B;
  cin >> S;

  for (int i = 0; i < N; i++) {
    if (S[i] == 'a') {

      if ((A + B) > ab) {
        ab++;
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    } else if (S[i] == 'b') {

      if ((A + B) > ab && b < B) {
        ab++;
        b++;

        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    } else {
      cout << "No" << endl;
    }
  }
  return 0;
}
