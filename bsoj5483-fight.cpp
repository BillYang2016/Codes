#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=2005;

struct Dinic {
	struct Edge {
		int from,to,cap,flow;
		Edge(int x=0,int y=0,int c=0,int f=0):from(x),to(y),cap(c),flow(f) {}
	};
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
		fill(vst+1,vst+n+1,0);
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

int n,m,step=0,top=0,BCC=0,Dfn[maxn],Lowlink[maxn],Stack[maxn],Belong[maxn],Deg[maxn];
bool Instack[maxn],flag[maxn][maxn];
char mp[maxn][maxn];
vector<int> edges[maxn];

void Tarjan(int Now) {
	Dfn[Now]=Lowlink[Now]=++step;
	Instack[Stack[++top]=Now]=1;
	for(int Next:edges[Now]) {
		if(!Dfn[Next])Tarjan(Next),Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
		else if(Instack[Next])Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
	}
	if(Dfn[Now]==Lowlink[Now]) {
		BCC++;
		int y;
		do {
			y=Stack[top--];
			Instack[y]=0;
			Belong[y]=BCC;
		} while(y!=Now);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	int S=n+m+1,T=n+m+2;
	dinic.init(T);
	for(int i=1; i<=n; i++) {
		scanf("%s",mp[i]+1);
		for(int j=1; j<=m; j++)if(mp[i][j]=='1')dinic.AddEdge(i,n+j,1);
	}
	for(int i=1; i<=n; i++)dinic.AddEdge(S,i,1);
	for(int i=1; i<=m; i++)dinic.AddEdge(n+i,T,1);
	int ans=dinic.maxflow(S,T);
	if(ans<n) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++)putchar('1');
			putchar('\n');
		}
		return 0;
	}
	for(auto e:dinic.edges) {
		if(e.from>e.to||e.from>n+m||e.to>n+m)continue;
		if(e.cap==e.flow) {flag[e.from][e.to-n]=1;edges[e.to].push_back(e.from);Deg[e.to-n]=1;}
		else edges[e.from].push_back(e.to);
	}
	for(int i=1; i<=n+m; i++)if(!Dfn[i])Tarjan(i);
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++)
			if(mp[i][j]=='1'&&(Belong[i]==Belong[n+j]||!Deg[j]||flag[i][j]))putchar('0');
			else putchar('1');
		putchar('\n');
	}
	return 0;
}