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

const int maxn=55;

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
	int AddEdge(int x,int y,int v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
		return m-2;
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

int n,s1,t1,s2,t2,v1,v2,map[maxn][maxn];

bool Check() {
	int S=n+1,T=n+2;
	dinic.init(T);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			if(map[i][j]==1)dinic.AddEdge(i,j,INT_MAX/2);
			else if(map[i][j]==2)dinic.AddEdge(i,j,2);
		}
	dinic.AddEdge(S,s1,v1);
	dinic.AddEdge(S,s2,v2);
	dinic.AddEdge(t1,T,v1);
	dinic.AddEdge(t2,T,v2);
	if(dinic.maxflow(S,T)<v1+v2)return false;
	return true;
} 

int main() {
	while(~scanf("%d",&n)) {
		s1=Get_Int()+1;
		t1=Get_Int()+1;
		v1=Get_Int()*2;
		s2=Get_Int()+1;
		t2=Get_Int()+1;
		v2=Get_Int()*2;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++) {
				char x=' ';
				while(!isalpha(x))x=getchar();
				if(x=='N')map[i][j]=1;
				else if(x=='O')map[i][j]=2;
				else map[i][j]=0;
			}
		if(!Check()) {
			puts("No");
			continue;
		}
		swap(s2,t2);
		if(!Check()) {
			puts("No");
			continue;
		}
		puts("Yes");
	}
	return 0;
} 
