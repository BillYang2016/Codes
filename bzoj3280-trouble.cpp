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
	int from,to,cap,flow,cost;
	Edge(int x=0,int y=0,int c=0,int f=0,int co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

struct zkw_CostFlow {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn],vst[maxn];
	int dist[maxn],path[maxn];
	int flow,cost;
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,int v,int f) {
		edges.push_back(Edge(x,y,v,0,f));
		edges.push_back(Edge(y,x,0,0,-f));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool spfa() {
		for(int i=1; i<=n; i++)dist[i]=INT_MAX;
		memset(inque,0,sizeof(inque));
		dist[t]=0;
		inque[t]=1;
		deque<int>Q;
		Q.push_back(t);
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop_front();
			inque[Now]=0;
			for(int id:G[Now]) {
				Edge& e=edges[id^1];
				int Next=e.from;
				if(dist[Next]>dist[Now]+e.cost&&e.cap>e.flow) {
					dist[Next]=dist[Now]+e.cost;
					if(!inque[Next]) {
						inque[Next]=1;
						if(!Q.empty()&&dist[Next]<dist[Q.front()])Q.push_front(Next);
						else Q.push_back(Next);
					}
				}
			}
		}
		return dist[s]<INT_MAX;
	}
	int dfs(int Now,int a) {
		if(vst[Now])return 0;
		if(Now==t||a==0)return a;
		int flow=0;
		vst[Now]=1;
		for(int id:G[Now]) {
			Edge& e=edges[id];
			int Next=e.to;
			if(dist[Now]-e.cost!=dist[Next])continue;
			int nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(nextflow>0) {
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

int T,n,m,k,sum=0;

int main() {
	T=Get_Int();
	for(int t=1; t<=T; t++) {
		n=Get_Int();
		m=Get_Int();
		k=Get_Int();
		sum=0;
		int S=2*n+1,T=2*n+2;
		zkw.init(T);
		for(int i=1; i<=n; i++) {
			int v=Get_Int();
			sum+=v;
			zkw.AddEdge(S,n+i,v,0);
			zkw.AddEdge(i,T,v,0);
			if(i<n)zkw.AddEdge(i,i+1,INT_MAX,0);
		}
		for(int i=1; i<=m; i++) {
			int v=Get_Int(),f=Get_Int();
			zkw.AddEdge(S,1,v,f);
		}
		for(int i=1; i<=k; i++) {
			int d=Get_Int(),f=Get_Int();
			for(int j=1; j+d+1<=n; j++)zkw.AddEdge(n+j,j+d+1,INT_MAX,f);
		}
		int flow=zkw.maxflow(S,T);
		if(flow!=sum)printf("Case %d: impossible\n",t);
		else printf("Case %d: %d\n",t,zkw.cost);
	}
	return 0;
}
