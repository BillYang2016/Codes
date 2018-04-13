#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

struct Edge {
	int from,to,cap,flow;
	Edge(int x=0,int y=0,int v=0,int f=0):from(x),to(y),cap(v),flow(f) {}
};

struct Dinic {
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int dist[maxn],cur[maxn];
	bool vst[maxn];
	void init(int n) {
		this->n=n;
		// edges.clear();
		// for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,int v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bfs() {
		fill(vst+1,vst+n+1,0);
		queue<int> Q;
		Q.push(t);
		vst[t]=1;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			for(int id:G[Now]) {
				Edge e=edges[id^1];
				int Next=e.from;
				if(!vst[Next]&&e.cap>e.flow) {
					vst[Next]=1;
					dist[Next]=dist[Now]+1;
					if(Next==s)return 1;
					Q.push(Next);
				}
			}
		}
		return vst[s];
	}
	int dfs(int Now,int a) {
		if(Now==t||a==0)return a;
		int flow=0;
		for(int &i=cur[Now]; i<G[Now].size(); i++) {
			Edge &e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Next]!=dist[Now]-1)continue;
			int nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(nextflow) {
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

int n,m,s,t;

int main() {
	n=Get_Int();
	m=Get_Int();
	s=Get_Int();
	t=Get_Int();
	dinic.init(n);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		dinic.AddEdge(x,y,v);
	}
	printf("%d\n",dinic.maxflow(s,t));
	return 0;
}