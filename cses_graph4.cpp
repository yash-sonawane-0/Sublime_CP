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

int n, m;
vector<int> adj[N];
vector<int> vis(N, 0);

void yash()
{
  cin >> n >> m;
  for(int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  queue<int> q;
  q.push(1);
  map<int, int> parent;
  int gotIt = 0;
  vis[1] = 1;

  while(!q.empty()){
    int node = q.front();
    q.pop();

    if(node == n){
      gotIt = 1;
      break;
    }

    for(auto it : adj[node]) {
      if(vis[it] == 0) {
        parent[it] = node;
        vis[it] = 1;
        q.push(it);
      }
    }
  }

  if(gotIt == 0) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  int curr = n;
  vector<int> ans;
  ans.push_back(curr);
  while(1) {
    if(curr == 1){
      break;
    }
    ans.push_back(parent[curr]);
    curr = parent[curr];
  }

  reverse(all(ans));
  cout << ans.size() << '\n';
  pVec(ans);

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