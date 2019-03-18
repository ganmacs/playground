// #include <algorithm>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include <cstdio>
// #include <cmath>
// #include <queue>
// #include <stack>
// #include <map>
// #include <set>

// using namespace std;

// const int MAX = 100000;

// struct Node { int p, l, r; };
// Node t[1000];

// int PRE[100];
// int IN[100];
// int N;

// void postorder(int id) {
//   if (t[id].l != -1) postorder(t[id].l);
//   if (t[id].r != -1) postorder(t[id].r);
//   printf(" %d", id);
// }

// // int myfind(int i, int j, vector<int> vec) {
// // for (; j < N; j++) {
// //   if (IN[i] == PRE[j]) break;
// //   vec.push_back(PRE[j]);
// // }
// // IN[i]

// //         t[id].p = prev;
// //         // t[prev].p = id;
// //         prev = PRE[j];
// //         break;
// //       }

// //       prev = PRE[j];
// //       vec.push_back(PRE[j]);
// // while (!vec.empty()) {
// // }





// // return 0;
// // }

// int main(int argc, char *argv[]) {
//   int  v, root;
//   vector<vector<int>> vec;
//   cin >> N;

//   for (int i = 0; i < N; i++) {
//     cin >> PRE[i];
//     if (i == 0) root = PRE[i];
//   }

//   for (int i = 0; i < N; i++) cin >> IN[i];

//   int j = 0, prev = -1;
//   for (int i = 0; i < N; i++) {
//     int id = IN[i];

//     if (find(vec.front().begin(), vec.front().end(), id) == vec.end()) {
//       prev = -1;
//       vector<int> v2;
//       for (; j < N; j++) {
//         v2.push_back(id);
//         if (id == PRE[j]) {
//           j++;
//           break;
//         }
//       }

//       if (!v2.empty()) {
//         vec.push_back(v2);
//       }
//     }

//     if (vec.front().size() == 1) {

//     } else {
//       int kk = vec.front().front();
//       vec.front().pop_back();
//       if (prev != -1) {
//         t[id].l = prev;
//         t[prev].p = id;
//       }
//       prev = kk;
//     }
//   }
// }

// // myfind(0, 0, vec);


// // int j = 0, prev = -1;
// //   int id = IN[i];
// //   if (find(vec.begin(), vec.end(), id) == vec.end()) {
// //     for (; j < N; j++) {
// //       if (id == PRE[j]) {
// //         t[id].p = prev;
// //         // t[prev].p = id;
// //         prev = PRE[j];
// //         break;
// //       }

// //       prev = PRE[j];
// //       vec.push_back(PRE[j]);
// //     }

// //     // if (j != N)?
// //     // prev = PRE[j];
// //   } else {
// //     while (!vec.empty()) {
// //       int fv = vec.front();
// //       vec.pop_back();
// //       if (fv == id) {
// //         t[id].l = prev;
// //         // t[prev].p = id;
// //         prev = id;
// //         break;
// //       }
// //     }
// //   }
// // }

// postorder(root);
// cout << endl;
// return 0;
// }
