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

const int maxnode=11005,maxn=105,maxid=1005;

struct Edge {
	int from,to,cap,flow;
	Edge(int x=0,int y=0,int c=0,int f=0):from(x),to(y),cap(c),flow(f) {}
};

struct Dinic {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxnode];
	bool vst[maxnode];
	int dist[maxnode],cur[maxnode];
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
		Q.push(t); //reversed
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

int n,m,cnt=0,sum=0,id[maxn],num[maxn][maxn],vst[maxid];

int main() {
	n=Get_Int();
	m=Get_Int();
	int S=n*n+1000,T=S+1;
	for(int i=1; i<=n; i++) {
		id[i]=Get_Int();
		cnt=max(cnt,id[i]);
		if(!vst[id[i]]) {
			dinic.AddEdge(id[i],T,m*id[i]*id[i]);
			vst[id[i]]=1;
		}
	}
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++) {
			num[i][j]=++cnt;
			int v=Get_Int();
			if(v>=0) {
				dinic.AddEdge(S,num[i][j],v);
				sum+=v;
			} else dinic.AddEdge(num[i][j],T,-v);
		}
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++) {
			if(num[i][j-1])dinic.AddEdge(num[i][j],num[i][j-1],INT_MAX);
			if(num[i+1][j])dinic.AddEdge(num[i][j],num[i+1][j],INT_MAX);
		}
	for(int i=1; i<=n; i++) {
		dinic.AddEdge(num[i][i],T,id[i]);
		dinic.AddEdge(num[i][i],id[i],INT_MAX);
	}
	printf("%d\n",sum-dinic.maxflow(S,T));
	return 0;
} 
