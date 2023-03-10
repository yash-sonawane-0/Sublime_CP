bool toposort(int n) //Returns 1 if there exists a toposort, 0 if there is a cycle
{	
	queue<int> q;
	vector<int> indeg(n + 1, 0);
	for(int i = 1; i <= n; i++)
		for(auto &it:adj[i]){
			// cout << char(i + 'a' - 1) << " " << it << '\n';
			indeg[it]++;
		}
	for(int i = 1; i <= n; i++)
	{
		if(!indeg[i]){
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		ans.push_back(u);
		for(auto &v:adj[u])
		{
			indeg[v]--;
			if(!indeg[v])
				q.push(v);
		}
	}
	return ans.size() == n;
}