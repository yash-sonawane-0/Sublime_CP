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
const int N = 1e5 + 7;

void init_code() {
#ifndef ONLINE_JUDGE
  freopen("inputf.txt", "r", stdin);
  freopen("outputf.txt", "w", stdout);
#endif // ONLINE_JUDGE
}

/*
https://leetcode.com/contest/biweekly-contest-98/problems/handling-sum-queries-after-update/
*/

int a[N];
class node {
public:
	static const int inf = 1e18;
	int mn, mx, sum;
	node(int _mn, int _mx, int _sum) {
		mn = _mn;
		mx = _mx;
		sum = _sum;
	}
	node() {
		mn = inf;
		mx = -inf;
		sum = 0;
	}
};
struct segtree {
	int N;
	vector<node> st;
	vector<bool> cLazy;
	vector<int> lazy;
	vector<int> tree;
	void init(int n) {
		N = n;
		st.resize((N << 2) + 2);
		cLazy.assign((N << 2) + 2, false);
		lazy.assign((N << 2) + 2, 0);
		tree.assign((N << 2) + 2, 0);
		build(1, 1, N);
	}

	//Write reqd merge functions
	void merge(node &ret, node &left, node &right) {
		ret.mn = min(left.mn, right.mn);
		ret.mx = max(left.mx, right.mx);
		ret.sum = left.sum + right.sum;
	}

	//Handle lazy propagation appriopriately
	void propagate(int u, int L, int R) {
		// Propagate down?
		if (L != R) {
			// cLazy[u * 2] = 1;
			// cLazy[u * 2 + 1] = 1;
			cLazy[u * 2] = !cLazy[u * 2];
			cLazy[u * 2 + 1] = !cLazy[u * 2 + 1];
			// Default range update operation is :
			// adding lazy[u] to all elements in range [...]
			lazy[u * 2] += lazy[u];
			lazy[u * 2 + 1] += lazy[u];
		}
		// Updating the range [L, R] with lazy[u]
		{
			// Default range update operation is :
			// adding lazy[u] to all elements in range [...]
			st[u].sum += (R - L + 1) - st[u].sum;
			st[u].mx += lazy[u];
			st[u].mn += lazy[u];
		}
		cLazy[u] = 0;

		// flip(u, L, R);
		lazy[u] = 0;
	}

	// void flip(int u, int L, int R) {
  //   st[u].sum = (R - L + 1) - st[u].sum;  // Flip 0/1.
  //   if (L != R) {
  //     cLazy[u * 2] = !cLazy[u * 2];
	// 		cLazy[u * 2 + 1] = !cLazy[u * 2 + 1];
  //   }
  // }

	void build (int u, int L, int R) {
		if (L == R) {
			// Leaf value
			tree[u] = a[L];
			st[u] = node(a[L], a[L], a[L]);
			return;
		}
		int M = (L + R) / 2;
		build(u * 2, L, M);
		build(u * 2 + 1, M + 1, R);
		merge(st[u], st[u * 2], st[u * 2 + 1]);
	}
	node Query(int u, int L, int R, int i, int j) {
		if (cLazy[u])
			propagate(u, L, R);
		if (j < L || i > R)
			return node();
		if (i <= L && R <= j)
			return st[u];
		int M = (L + R) / 2;
		node left = Query(u * 2, L, M, i, j);
		node right = Query(u * 2 + 1, M + 1, R, i, j);
		node ret;
		merge(ret, left, right);
		return ret;
	}

	node pQuery(int u, int L, int R, int pos) {
		if (cLazy[u])
			propagate(u, L, R);
		if (L == R)
			return st[u];
		int M = (L + R) / 2;
		if (pos <= M)
			return pQuery(u * 2, L, M, pos);
		else
			return pQuery(u * 2 + 1, M + 1, R, pos);
	}

	void Update(int u, int L, int R, int i, int j, int val) {
		if (cLazy[u])
			propagate(u, L, R);
		if (j < L || i > R)
			return;
		if (i <= L && R <= j) {
			// Default range update operation is :
			// adding val to all elements in range [...]
			// cLazy[u] = 1;
			// lazy[u] = val;
			propagate(u, L, R);
			lazy[u] = 1;
			// flip(u, L, R);
			return;
		}
		int M = (L + R) / 2;
		Update(u * 2, L, M, i, j, val);
		Update(u * 2 + 1, M + 1, R, i, j, val);
		tree[u] = tree[u * 2] + tree[u * 2 + 1];
		merge(st[u], st[u * 2], st[u * 2 + 1]);
	}

	void pUpdate(int u, int L, int R, int pos, int val) {
		if (cLazy[u])
			propagate(u, L, R);
		if (L == R) {
			cLazy[u] = 1;
			lazy[u] = val;
			propagate(u, L, R);
			return;
		}
		int M = (L + R) / 2;
		if (pos <= M)
			pUpdate(u * 2, L, M, pos, val);
		else
			pUpdate(u * 2 + 1, M + 1, R, pos, val);
		merge(st[u], st[u * 2], st[u * 2 + 1]);
	}
	node query(int pos) { return pQuery(1, 1, N, pos); }
	node query(int l, int r) { return Query(1, 1, N, l, r); }
	void update(int pos, int val) { pUpdate(1, 1, N, pos, val); }
	void update(int l, int r, int val) { Update(1, 1, N, l, r, val); }

	int getTreeSum() {
		return st[1].sum;
	}
};

void yash()
{
  int n, sum = 0;
  cin >> n; 
  vector<int> A(n), B(n);
  for(int i = 0; i < n; i++) {
  	cin >> A[i];
  	a[i + 1] = A[i];
  }
  for(int i = 0; i < n; i++) {
  	cin >> B[i];
  	sum += B[i];
  }

  segtree seg;
  seg.init(n + 2);

  int ans = sum;

  int m;
  cin >> m;
  for(int i = 0; i < m; i++) {
  	int x, l, r;
  	cin >> x >> l >> r;
  	if(x == 1) {
  		l++, r++;
  		seg.update(l, r, 0);
  	}
  	else if(x == 2) {
  		int t = seg.getTreeSum();
  		ans += (t * l);
  	}
  	else {
  		cout << ans << '\n';
  	}
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