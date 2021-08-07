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

struct UnionFind {
    vector<int> par;

    UnionFind(int n) : par(n, -1) { }

    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }

    bool issame(int x, int y) {
        return root(x) == root(y);
    }

    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y); // merge technique
        par[x] += par[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return -par[root(x)];
    }
};

using pint = pair<int,int>;
int main () {
    int N, M, K;
    cin >> N >> M >> K;
    vector<set<int> > dame(N);
    UnionFind uf(N);
    for (int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b; --a, --b;
        dame[a].insert(b);
        puts("\n===================================== start print");
        printf("%d %d\n", a, b);
        puts("===================================== finish print\n");
        dame[b].insert(a);
        // uf.merge(a, b);
    }
    for (int i = 0; i < K; ++i) {
        int c, d; cin >> c >> d; --c, --d;
        if (!uf.issame(c, d)) continue;
        dame[c].insert(d);
        dame[d].insert(c);
    }



    for (int i = 0; i < N; ++i) {
        // int mem = uf.size(i) - 1; // 同じ連結成分の「自分以外」の人数

        int mem = dame[i].size(); // その中ですでに友達かブロック関係の人数
        cout << mem << " ";
    }
    cout << endl;
}
