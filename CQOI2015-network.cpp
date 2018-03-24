#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define pii pair<LL,int>

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;

struct Edge {int from,to,dist;};

int n,m;
LL dist[maxn];
bool vst[maxn];
vector<Edge> edges[maxn];

void AddEdge(int x,int y,int v) {edges[x].push_back((Edge) {x,y,v});}

void Dijkstra(int s) {
	for(int i=1; i<=n; i++)dist[i]=LLONG_MAX/2;
	priority_queue<pii,vector<pii>,greater<pii> > Q;
	Q.push(pii(dist[s]=0,s));
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(Edge &e:edges[Now]) {
			int Next=e.to;
			if(dist[Next]>dist[Now]+e.dist) {
				dist[Next]=dist[Now]+e.dist;
				Q.push(pii(dist[Next],Next));
			}
		}
	}
}

struct Dinic {
	struct Edge {
		int from,to;
		LL cap,flow;
		Edge(int x=0,int y=0,LL c=0,LL v=0):from(x),to(y),cap(c),flow(v) {}
	};
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool vst[maxn];
	int dist[maxn],cur[maxn];
	void init(int n) {this->n=n;}
	void AddEdge(int x,int y,LL v) {
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
				Edge &e=edges[id^1];
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
	LL dfs(int Now,LL a) {
		if(Now==t||a==0)return a;
		LL flow=0;
		for(int i=cur[Now]; i<G[Now].size(); i++) {
			Edge &e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			LL nextflow=dfs(Next,min(a,e.cap-e.flow));
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

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	Dijkstra(1);
	dinic.init(2*n);
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		if(i==1||i==n)dinic.AddEdge(i,n+i,LLONG_MAX/2);
		else dinic.AddEdge(i,n+i,x);
	}
	for(int Now=1; Now<=n; Now++)
		for(Edge &e:edges[Now])
			if(dist[e.to]==dist[Now]+e.dist)dinic.AddEdge(n+Now,e.to,LLONG_MAX/2);
	printf("%lld\n",dinic.maxflow(1,2*n));
	return 0;
}