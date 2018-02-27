#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=50005;

struct Edge {
	int from,to;
	LL cap,flow;
	Edge(int x=0,int y=0,LL c=0,LL f=0):from(x),to(y),cap(c),flow(f) {}
};

struct Dinic {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool vst[maxn];
	int dist[maxn],cur[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,LL v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bfs() {
		memset(vst,0,sizeof(vst));
		memset(dist,0,sizeof(dist));
		queue<int>Q;
		Q.push(t);
		vst[t]=1;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			for(int id:G[Now]) {
				Edge& e=edges[id^1];
				int Next=e.from;
				if(!vst[Next]&&e.cap>e.flow) { 
					vst[Next]=1;
					dist[Next]=dist[Now]+1;
					Q.push(Next);
				}
			}
		}
		return vst[s];
	}
	LL dfs(int Now,LL a) {
		if(Now==t||a==0)return a;
		LL flow=0;
		for(int& i=cur[Now]; i<G[Now].size(); i++) {
			Edge& e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			LL nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(nextflow>0) {
				e.flow+=nextflow;
				edges[G[Now][i]^1].flow-=nextflow;
				flow+=nextflow;
				a-=nextflow;
				if(a==0)break;
			}
		}
		return flow;
	}
	LL maxflow(int s,int t) {
		this->s=s;
		this->t=t;
		LL flow=0;
		while(bfs()) {
			memset(cur,0,sizeof(cur));
			flow+=dfs(s,LLONG_MAX);
		}
		return flow;
	}
} dinic;

int n,m,cnt=0,id[105][105];
LL sum=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	int S=5*n*m+1,T=5*n*m+2;
	dinic.init(T);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			int v=Get_Int();
			sum+=v;
			id[i][j]=++cnt;
			dinic.AddEdge(S,id[i][j],v);
		}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			int v=Get_Int();
			sum+=v;
			dinic.AddEdge(id[i][j],T,v);
		}
	for(int i=1; i<n; i++)
		for(int j=1; j<=m; j++) {
			int v=Get_Int();
			sum+=v;
			cnt++;
			dinic.AddEdge(S,cnt,v);
			dinic.AddEdge(cnt,id[i][j],LLONG_MAX/2);
			dinic.AddEdge(cnt,id[i+1][j],LLONG_MAX/2);
		}
	for(int i=1; i<n; i++)
		for(int j=1; j<=m; j++) {
			int v=Get_Int();
			sum+=v;
			cnt++;
			dinic.AddEdge(cnt,T,v);
			dinic.AddEdge(id[i][j],cnt,LLONG_MAX/2);
			dinic.AddEdge(id[i+1][j],cnt,LLONG_MAX/2);
		}
	for(int i=1; i<=n; i++)
		for(int j=1; j<m; j++) {
			int v=Get_Int();
			sum+=v;
			cnt++;
			dinic.AddEdge(S,cnt,v);
			dinic.AddEdge(cnt,id[i][j],LLONG_MAX/2);
			dinic.AddEdge(cnt,id[i][j+1],LLONG_MAX/2);
		}
	for(int i=1; i<=n; i++)
		for(int j=1; j<m; j++) {
			int v=Get_Int();
			sum+=v;
			cnt++;
			dinic.AddEdge(cnt,T,v);
			dinic.AddEdge(id[i][j],cnt,LLONG_MAX/2);
			dinic.AddEdge(id[i][j+1],cnt,LLONG_MAX/2);
		}
	printf("%lld\n",sum-dinic.maxflow(S,T));
	return 0;
}