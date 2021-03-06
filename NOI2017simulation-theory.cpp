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

const int maxn=105;
 
struct Edge {
	int from,to,cap,flow;
	Edge(int x=0,int y=0,int c=0,int f=0):from(x),to(y),cap(c),flow(f) {}
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
	void AddEdge(int x,int y,int v) {
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
		Q.push(t); //反向层次图
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
	int dfs(int Now,int a) {
		if(Now==t||a==0)return a;
		int flow=0;
		for(int& i=cur[Now]; i<G[Now].size(); i++) {
			Edge& e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			int nextflow=dfs(Next,min(a,e.cap-e.flow));
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
	int maxflow(int s,int t) {
		this->s=s;
		this->t=t;
		int flow=0;
		while(bfs()) {
			memset(cur,0,sizeof(cur));
			flow+=dfs(s,INT_MAX);
		}
		return flow;
	}
} dinic;

int t,n,a[maxn];
vector<int>edges1[maxn],edges2[maxn];

void AddEdge1(int x,int y) {
	edges1[x].push_back(y);
}

void AddEdge2(int x,int y) {
	edges2[x].push_back(y);
}

void Dfs1(int Now,int fa) {
	if(fa)dinic.AddEdge(Now,fa,INT_MAX/2);
	for(int Next:edges1[Now]) {
		if(Next==fa)continue;
		Dfs1(Next,Now);
	}
}

void Dfs2(int Now,int fa) {
	if(fa)dinic.AddEdge(Now,fa,INT_MAX/2);
	for(int Next:edges2[Now]) {
		if(Next==fa)continue;
		Dfs2(Next,Now);
	}
}

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		for(int i=1; i<=n; i++)edges1[i].clear(),edges2[i].clear();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge1(x,y);
			AddEdge1(y,x);
		}
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge2(x,y);
			AddEdge2(y,x);
		}
		int ans=0;
		for(int i=1; i<=n; i++) {
			int S=n+1,T=n+2,sum=0;
			dinic.init(n+2);
			Dfs1(i,0);
			Dfs2(i,0);
			for(int i=1; i<=n; i++) {
				if(a[i]>=0) {
					dinic.AddEdge(S,i,a[i]);
					sum+=a[i];
				} else dinic.AddEdge(i,T,-a[i]);
			}
			ans=max(ans,sum-dinic.maxflow(S,T));
		}
		printf("%d\n",ans);
	}
	return 0;
} 
