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

const int MAX = 100000;

vector<int> children[MAX];
int p[MAX];
int d[MAX];
int types[MAX];

void set_depth(int id, int dep) {
  if (children[id].empty()) {
    types[id] = 0;
  }

  for (int i = 0; i < children[id].size(); i++) {
    int c = children[id][i];
    d[c] = dep;
    set_depth(c, dep + 1);
  }
}

int main(int argc, char *argv[])
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    p[i] = -1;
    d[i] = 0;
    types[i] = 1;
  };

  for (int i = 0; i < N; i++) {
    int id, k;
    vector<int> vec;
    cin >> id >> k;

    for (int j = 0; j < k; j++) {
      int v;
      cin >> v;
      vec.push_back(v);
      p[v] = id;
    }

    children[id] = vec;
  }

 int root_id = -1;
 for (int i = 0; i < N; i++) {
   if (p[i] == -1) {
     root_id = i;
     break;
   }
 }

 set_depth(root_id, 1);
 types[root_id] = 2;

 for (int i = 0; i < N; i++) {
   printf("node %d: ", i);
   printf("parent = %d, ", p[i]);
   printf("depth = %d, ", d[i]);
   if (types[i] == 0) {
     printf("leaf, ");
   } else if(types[i] == 2) {
     printf("root, ");
   } else {
     printf("internal node, ");
   }

   cout << "[";
   for (int j = 0; j < children[i].size(); j++) {
     if (j != 0) cout << ", ";
     cout << children[i][j];
   }
   cout << "]";

   cout << endl;
 }

 return 0;
}
