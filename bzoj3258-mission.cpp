#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=4505;

struct Edge {int from,to,dist;};

int n,m,top=0,step=0,BCC=0,cnt=0,a[maxn],Belong[maxn],Dfn[maxn],Lowlink[maxn],Stack[maxn];
LL dist1[maxn],dist2[maxn];
bool vst[maxn],Instack[maxn];
vector<Edge> edges[maxn];

void Clear() {
	step=BCC=0;
	for(int i=1; i<=cnt; i++) {
		edges[i].clear();
		Dfn[i]=0;
	}
}

#define pii pair<LL,int>

void Dijkstra(int s,LL *dist) {
	fill(dist,dist+n+1,LLONG_MAX/2),fill(vst,vst+n+1,0);
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
		Edge(int x=0,int y=0,LL c=0,LL f=0):from(x),to(y),cap(c),flow(f) {}
	};
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool vst[maxn];
	int dist[maxn],cur[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
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
	LL dfs(int Now,LL a) {
		if(Now==t||a==0)return a;
		LL flow=0;
		for(int& i=cur[Now]; i<G[Now].size(); i++) {
			Edge& e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			LL nextflow=dfs(Next,min(a,e.cap-e.flow));
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

void Tarjan(int Now) {
	Dfn[Now]=Lowlink[Now]=++step;
	Stack[++top]=Now;
	Instack[Now]=1;
	for(int id:dinic.G[Now]) {
		auto &e=dinic.edges[id];
		if(e.flow==e.cap)continue;
		int Next=e.to;
		if(!Dfn[Next]) {Tarjan(Next);Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);}
		else if(Instack[Next])Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
	}
	if(Dfn[Now]==Lowlink[Now]) {
		BCC++;
		int y;
		do {
			y=Stack[top--];
			Belong[y]=BCC;
			Instack[y]=0;
		} while(y!=Now);
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		Clear();
		n=Get_Int();
		m=Get_Int();
		for(int i=1; i<n; i++)a[i]=Get_Int();
		a[n]=INT_MAX;
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int(),v=Get_Int();
			edges[x].push_back((Edge) {x,y,v});
			edges[y].push_back((Edge) {y,x,v});
		}
		Dijkstra(1,dist1);
		Dijkstra(n,dist2);
		dinic.init(cnt);
		cnt=n;
		for(int Now=1; Now<n; Now++)
			for(Edge &e:edges[Now]) {
				int Next=e.to;
				if(dist1[n]==dist1[Now]+e.dist+dist2[Next]) {
					cnt++; //!!!
					dinic.AddEdge(Now,cnt,a[Now]);
					dinic.AddEdge(cnt,Next,a[Next]);
				}
			}
		dinic.n=cnt;
		LL ans=dinic.maxflow(1,n);
		for(int i=1; i<=cnt; i++)if(!Dfn[i])Tarjan(i);
		bool bj=1;
		for(auto &e:dinic.edges) {
			int x=e.from,y=e.to;
			if(!e.cap||e.cap!=e.flow||Belong[x]==Belong[y]||(Belong[x]==Belong[1]&&Belong[y]==Belong[n]))continue;
			printf("No %lld\n",ans);
			bj=0;
			break;
		}
		if(bj)printf("Yes %lld\n",ans);
	}
	return 0;
}