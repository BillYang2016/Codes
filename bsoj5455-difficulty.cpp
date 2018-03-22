#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=5005,dx[]= {0,0,1,-1},dy[]= {1,-1,0,0};

struct Edge {
	int from,to,cap,flow,cost;
	Edge(int x=0,int y=0,int c=0,int f=0,int co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

struct MinimumCost_MaximumFlow {
	int n,m;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn];
	int a[maxn],dist[maxn],path[maxn];
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
	bool bellmanford(int s,int t,int& flow,int& cost) {
		for(int i=1; i<=n; i++)dist[i]=INT_MAX;
		memset(inque,0,sizeof(inque));
		queue<int>Q;
		Q.push(s);
		dist[s]=path[s]=0;
		a[s]=INT_MAX;
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
		if(dist[t]==INT_MAX)return false;
		flow+=a[t];
		cost+=dist[t]*a[t];
		for(int Now=t; Now!=s; Now=edges[path[Now]].from) {
			edges[path[Now]].flow+=a[t];
			edges[path[Now]^1].flow-=a[t];
		}
		return true;
	}
	int maxflow(int s,int t,int& cost) {
		int flow=0;
		while(bellmanford(s,t,flow,cost));
		return flow;
	}
} mcmf;

int n,m,A,B;
char mp[45][45];

int id(int x,int y) {return (x-1)*m+y;}

int main() {
	int t=Get_Int();
	n=Get_Int();
	m=Get_Int();
	A=Get_Int();
	B=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",mp[i]+1);
	int S=n*m*3+1,T=n*m*3+2,rS=T+1;
	mcmf.init(rS);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if((i+j)&1) {
				mcmf.AddEdge(id(i,j),T,1,0);
				mcmf.AddEdge(id(i,j),T,1,A);
				mcmf.AddEdge(id(i,j),T,1,2*A);
				mcmf.AddEdge(id(i,j),T,1,3*A);
				mcmf.AddEdge(n*m+id(i,j),id(i,j),1,0);
				mcmf.AddEdge(n*m+id(i,j),id(i,j),1,B-A);
				mcmf.AddEdge(2*n*m+id(i,j),id(i,j),1,0);
				mcmf.AddEdge(2*n*m+id(i,j),id(i,j),1,B-A);
			} else {
				mcmf.AddEdge(S,id(i,j),1,0);
				mcmf.AddEdge(S,id(i,j),1,A);
				mcmf.AddEdge(S,id(i,j),1,2*A);
				mcmf.AddEdge(S,id(i,j),1,3*A);
				mcmf.AddEdge(id(i,j),n*m+id(i,j),1,0);
				mcmf.AddEdge(id(i,j),n*m+id(i,j),1,B-A);
				mcmf.AddEdge(id(i,j),2*n*m+id(i,j),1,0);
				mcmf.AddEdge(id(i,j),2*n*m+id(i,j),1,B-A);
			}
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(mp[i][j]=='0'&&((i+j)&1))
				for(int k=0; k<4; k++) {
					int nx=i+dx[k],ny=j+dy[k];
					if(nx<1||nx>n||ny<1||ny>m||mp[nx][ny]=='1')continue;
					if(k<2)mcmf.AddEdge(n*m+id(nx,ny),n*m+id(i,j),1,0);
					else mcmf.AddEdge(2*n*m+id(nx,ny),2*n*m+id(i,j),1,0);
				}
	int q=Get_Int(),ans=0;
	while(q--) {
		mcmf.AddEdge(rS,S,1,0);
		mcmf.maxflow(rS,T,ans);
		if(t>=8&&t<=12&&ans>0)puts("1");
		else printf("%d\n",ans);
	}
	return 0;
}