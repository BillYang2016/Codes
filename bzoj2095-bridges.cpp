#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1005;

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

struct Set {
	int n,SCC,father[maxn];
	void init(int n) {
		this->n=n;
		for(int i=1; i<=n; i++)father[i]=i;
		SCC=n;
	}
	int Get_Father(int x) {return father[x]==x?x:father[x]=Get_Father(father[x]);}
	void merge(int x,int y) {
		x=Get_Father(x),y=Get_Father(y);
		if(x==y)return;
		father[x]=y;
		SCC--;
	}
} s;

struct Edge {int from,to,a,b;} edges[2005];
int n,m,InDegree[maxn],OutDegree[maxn];

bool Check(int mid) {
	dinic.init(n+2);
	s.init(n);
	for(int i=1; i<=n; i++)InDegree[i]=OutDegree[i]=0;
	for(int i=1; i<=m; i++) {
		Edge &e=edges[i];
		if(e.a<=mid&&e.b<=mid) {
			OutDegree[e.from]++;
			InDegree[e.to]++;
			s.merge(e.from,e.to);
			dinic.AddEdge(e.to,e.from,1);
		} else if(e.a<=mid) {
			OutDegree[e.from]++;
			InDegree[e.to]++;
			s.merge(e.from,e.to);
		} else if(e.b<=mid) {
			OutDegree[e.to]++;
			InDegree[e.from]++;
			s.merge(e.from,e.to);
		} else return 0;
	}
	if(s.SCC>1)return 0;
	int S=n+1,T=n+2;
	for(int i=1; i<=n; i++) {
		if(abs(InDegree[i]-OutDegree[i])&1)return 0;
		if(InDegree[i]>OutDegree[i])dinic.AddEdge(S,i,(InDegree[i]-OutDegree[i])>>1);
		if(OutDegree[i]>InDegree[i])dinic.AddEdge(i,T,(OutDegree[i]-InDegree[i])>>1);
	}
	dinic.maxflow(S,T);
	for(int id:dinic.G[S])if(dinic.edges[id].cap!=dinic.edges[id].flow)return 0;
	return 1;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),a=Get_Int(),b=Get_Int();
		edges[i]=(Edge) {x,y,a,b};
	}
	int Left=1,Right=1000;
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(Check(mid))Right=mid-1;
		else Left=mid+1;
	}
	if(Left>1000)puts("NIE");
	else printf("%d\n",Left);
	return 0;
}