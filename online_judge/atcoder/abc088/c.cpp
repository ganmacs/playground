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

int N[3][3];

int main(int argc, char *argv[])
{
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> N[i][j];
    }
  }

  int mina1 = min(min(N[0][0], N[0][1]), N[0][2]);
  int mina2 = min(min(N[1][0], N[1][1]), N[1][2]);
  int mina3 = min(min(N[2][0], N[2][1]), N[2][2]);
  int minb1 = min(min(N[0][0], N[1][0]), N[2][0]);
  int minb2 = min(min(N[0][1], N[1][1]), N[2][1]);
  int minb3 = min(min(N[0][2], N[1][2]), N[2][2]);

  for (int ia1 = 0; ia1 <= mina1; ia1++) {
    for (int ia2 = 0; ia2 <= mina2; ia2++) {
      for (int ia3 = 0; ia3 <= mina3; ia3++) {
        for (int jb1 = 0; jb1 <= minb1; jb1++) {
          for (int jb2 = 0; jb2 <= minb2; jb2++) {
            for (int jb3 = 0; jb3 <= minb3; jb3++) {
              if ((N[0][0] == ia1 + jb1) &&
                  (N[0][1] == ia1 + jb2) &&
                  (N[0][2] == ia1 + jb3) &&
                  (N[1][0] == ia2 + jb1) &&
                  (N[1][1] == ia2 + jb2) &&
                  (N[1][2] == ia2 + jb3) &&
                  (N[2][0] == ia3 + jb1) &&
                  (N[2][1] == ia3 + jb2) &&
                  (N[2][2] == ia3 + jb3)) {
                puts("Yes");
                return 0;
              }
            }
          }
        }
      }
    }
  }

  puts("No");
}
