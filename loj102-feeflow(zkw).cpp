#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=405; 

struct Edge {
	int from,to,cap,flow,cost;
	Edge(int x=0,int y=0,int c=0,int f=0,int v=0):from(x),to(y),cap(c),flow(f),cost(v) {}
};

struct zkw_CostFlow {
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	int dist[maxn],flow,cost;
	bool vst[maxn],inque[maxn];
	void init(int n) {
		this->n=n;
		// edges.clear();
		// for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,int v,int f) {
		edges.push_back(Edge(x,y,v,0,f));
		edges.push_back(Edge(y,x,0,0,-f));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool spfa() {
		fill(inque+1,inque+n+1,0);
		fill(dist+1,dist+n+1,INT_MAX);
		dist[t]=0;
		inque[t]=1;
		deque<int> Q;
		Q.push_back(t);
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop_front();
			inque[Now]=0;
			for(int id:G[Now]) {
				Edge &e=edges[id^1];
				int Next=e.from;
				if(dist[Next]>dist[Now]+e.cost&&e.cap>e.flow) {
					dist[Next]=dist[Now]+e.cost;
					if(!inque[Next]) {
						inque[Next]=1;
						if(!Q.empty()&&dist[Q.front()]>dist[Next])Q.push_front(Next);
						else Q.push_back(Next);
					}
				}
			}
		}
		return dist[s]!=INT_MAX;
	}
	int dfs(int Now,int a) {
		if(vst[Now])return 0;
		if(Now==t||a==0)return a;
		int flow=0;
		vst[Now]=1;
		for(int id:G[Now]) {
			Edge &e=edges[id];
			int Next=e.to;
			if(dist[Next]!=dist[Now]-e.cost)continue;
			int nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(nextflow) {
				cost+=nextflow*e.cost;
				e.flow+=nextflow;
				edges[id^1].flow-=nextflow;
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
		flow=cost=0;
		while(spfa()) {
			memset(vst,0,sizeof(vst));
			flow+=dfs(s,INT_MAX);
		}
		return flow;
	}
} zkw;

int n,m;

int main() {
	n=Get_Int();
	m=Get_Int();
	zkw.init(n);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int(),f=Get_Int();
		zkw.AddEdge(x,y,v,f);
	}
	int flow=zkw.maxflow(1,n);
	printf("%d %d\n",flow,zkw.cost);
	return 0;
}