//YashS
#include <bits/stdc++.h>
using namespace std;
#define test              int T;cin>>T;while(T--)
#define int               long long
#define pb                push_back
#define all(x)            (x).begin(),(x).end()
#define rep(i,a,b)        for(int i=a;i<b;i++)
#define pVec(v)           for(auto e:v)cout<<e<<" ";cout<<"\n"
const int MOD = 1e9 + 7;
const int N = 2e5 + 7;

void init_code() {
#ifndef ONLINE_JUDGE
  freopen("inputf.txt", "r", stdin);
  freopen("outputf.txt", "w", stdout);
#endif // ONLINE_JUDGE
}

/*
distance(u, v) = distance(u, CA) + distance(CA, v);
*/

int n, q;
vector<vector<int>> adj;
vector<int> lvl(N, 0);

int up[N][20];  // NlogN

// to calulcate level of each node
void dfs(int node, int par, int level = 0) {
    lvl[node] = level;
    for(auto it: adj[node]) {
        if(it != par) {
            dfs(it, node, level + 1);
        }
    }
} 

void binary_lifting(int node, int par)
{
    up[node][0] = par;
    for(int i = 1; i < 20; i++)
    {
        if(up[node][i-1] != -1)
            up[node][i] = up[up[node][i-1]][i-1];  // up[node][2^i level above] -> up[x][2^(i - 1) level] ; x node is -> 2^(i - 1) level above this node
        else up[node][i] = -1;
    }
 
    for(int it : adj[node])
    {
    if(it != par)
            binary_lifting(it, node);
    }
}
 
int lift_node(int node, int jump_required)
{
    if(node == -1 || jump_required == 0)
        return node;
    
    // breaking k in bits, and jumping from maximum (two power) set bit
    for(int i = 19; i >= 0; i--){
        if(jump_required >= (1<<i)){
            return lift_node(up[node][i], jump_required - (1<<i));
        }
    }
    return 1;
}
 
// approach 1 -> log^2 n
int LCA1(int u, int v){

    // making v closer to root and u down
    if(lvl[u] < lvl[v]) {
        swap(u, v);
    }

    // lift u to the level of v
    u = lift_node(u, lvl[u] - lvl[v]);

    int l = 0, r = lvl[u];

    while(l < r) {
        int mid = (l + r) / 2;
        int x1 = lift_node(u, mid);
        int x2 = lift_node(v, mid);

        if (x1 == x2) {
            r = mid;
        } 
        else {
            l = mid + 1;
        }
    }

    return lift_node(u, l);
}

// approach 1 -> logn
int LCA2(int u, int v){

    // making v closer to root and u down
    if(lvl[u] < lvl[v]) {
        swap(u, v);
    }

    // lift u to the level of v
    u = lift_node(u, lvl[u] - lvl[v]);

    if (u == v) {
        return u;
    }

    for(int i = 19; i >= 0; i--) {
        if(up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return lift_node(u, 1);
}

void yash()
{
  cin >> n >> q;
  adj.resize(n + 1);
  vector<pair<int, int>> vec;
  for(int i = 2; i <= n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, -1);
  binary_lifting(1, -1);
  while(q--){
      int u, v;
      cin >> u >> v;
      // cout << LCA2(u, v) << '\n';
      int x = LCA2(u, v);
      int ans = (lvl[u] - lvl[x]) + (lvl[v] - lvl[x]);
      cout << ans << '\n';
  }

}

signed main()
{
  init_code();
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  // test
  yash();
  return 0;
}