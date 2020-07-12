#include<bits/stdc++.h>

using namespace std;

const int maxn=405;

typedef long long LL;

struct Edge {
	LL from,to,cap,flow,cost;
	Edge(LL x=0,LL y=0,LL c=0,LL f=0,LL co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

LL per[maxn];

struct MinimumCost_MaximumFlow { //EK Edition
	int n,m;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn];
	LL a[maxn],dist[maxn];
	int path[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,LL v,LL f) {
		edges.push_back(Edge(x,y,v,0,f));
		edges.push_back(Edge(y,x,0,0,-f));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bellmanford(int s,int t,LL& flow,LL& cost) {
		for(int i=1; i<=n; i++)dist[i]=LLONG_MAX/2;
		queue<int> Q;
		Q.push(s);
		dist[s]=path[s]=0;
		a[s]=LLONG_MAX/2;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			inque[Now]=0;
			for(int id:G[Now]) {
				Edge& e=edges[id];
				int Next=e.to;
				if(e.cap>e.flow&&dist[Next]>dist[Now]+e.cost) {
					dist[Next]=dist[Now]+e.cost;
					path[Next]=id;
					a[Next]=min(a[Now],e.cap-e.flow);
					if(!inque[Next]) {
						Q.push(Next);
						inque[Next]=1;
					}
				}
			}
		}
		if(dist[t]==LLONG_MAX/2)return false;
		flow+=a[t];
		cost+=dist[t]*a[t];
		for(int Now=t; Now!=s; Now=edges[path[Now]].from) {
			edges[path[Now]].flow+=a[t];
			edges[path[Now]^1].flow-=a[t];
		}
		return true;
	}
	LL maxflow(int s,int t,LL& cost) {
		LL flow=0;
		cost=0;
		while(bellmanford(s,t,flow,cost))per[flow]=cost;
		return flow;
	}
} mcmf;

void printFrac(LL u,LL d) {
	printf("%lld/%lld\n",u/__gcd(u,d),d/__gcd(u,d));
}

int n,m,q;

int main() {
	while(scanf("%d%d",&n,&m)!=EOF) {
		mcmf.init(n);
		for(int i=1; i<=m; i++) {
			LL x,y,v;
			scanf("%lld%lld%lld",&x,&y,&v);
			mcmf.AddEdge(x,y,1,v);
		}
		LL cost=0;
		LL flow=mcmf.maxflow(1,n,cost);
		scanf("%d",&q);
		for(int i=1; i<=q; i++) {
			LL u,v;
			scanf("%lld%lld",&u,&v);
			if(flow*u<v) {
				puts("NaN");
				continue;
			}
			LL intt=v/u;
			printFrac(per[intt]*u+(intt==flow?0:(per[intt+1]-per[intt])*(v-intt*u)),v);
		}
	}
	return 0;
}