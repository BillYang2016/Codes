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

const int maxn=10005;
 
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

const int Dirx[]= {0,1,-1,0,0},Diry[]= {0,0,0,1,-1};
int n,m,h,Delta;

int id(int x,int y,int z) {
	return (z-1)*n*m+(y-1)*n+m;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	h=Get_Int();
	Delta=Get_Int();
	int S=n*m*h+1,T=n*m*h+2;
	for(int x=1; x<=n; x++)
		for(int y=1; y<=m; y++)
			dinic.AddEdge(S,id(x,y,1),Get_Int());
	for(int z=2; z<h; z++)
		for(int x=1; x<=n; x++)
			for(int y=1; y<=m; y++) {
				dinic.AddEdge(id(x,y,z-1),id(x,y,z),Get_Int());
				if(z<Delta)continue;
				for(int k=1; k<=4; k++) {
					int nx=x+Dirx[k],ny=y+Diry[k];
					if(nx<1||ny<1||nx>n||ny>m)continue;
					dinic.AddEdge(id(x,y,z),id(nx,ny,z-Delta+1),INT_MAX/2);
				}
			}
	printf("%d\n",dinic.maxflow(S,T));
	return 0;
} 
