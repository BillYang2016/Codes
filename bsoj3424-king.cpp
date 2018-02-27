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

struct Edge {
	int from,to,cap,flow,cost;
	Edge(int x=0,int y=0,int c=0,int f=0,int co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

struct zkw_CostFlow {
	const static int maxn=2005;
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn],vst[maxn];
	int dist[maxn];
	int flow,cost;
	void init(int n) {
		this->n=n;
		edges.clear();
		flow=cost=0;
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
		while(spfa()) {
			memset(vst,0,sizeof(vst));
			flow+=dfs(s,INT_MAX);
		}
		return flow;
	}
} zkw;

const int maxn=1005;

int t,n,m,a,b,step=0,top=0,BCC=0,Start[maxn],End[maxn],Belong[maxn],Dfn[maxn],Lowlink[maxn],Stack[maxn],Instack[maxn];
vector<int> edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Tarjan(int Now) {
	Dfn[Now]=Lowlink[Now]=++step;
	Stack[++top]=Now;
	Instack[Now]=1;
	for(int Next:edges[Now]) {
		if(!Dfn[Next]) {
			Tarjan(Next);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
		} else if(Instack[Next])Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
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

void Clear() {
	for(int i=1; i<=n; i++)edges[i].clear();
	memset(Dfn,0,sizeof(Dfn));
	memset(Lowlink,0,sizeof(Lowlink));
	step=BCC=0;
}

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		a=Get_Int();
		b=Get_Int();
		Clear();
		for(int i=1; i<=a; i++)Start[i]=Get_Int();
		for(int i=1; i<=b; i++)End[i]=Get_Int();
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge(x,y);
		}
		for(int i=1; i<=n; i++)
			if(!Dfn[i])Tarjan(i);
		int fakeS=2*BCC+1,T=2*BCC+2,realS=T+1;
		zkw.init(T);
		for(int i=1; i<=a; i++)zkw.AddEdge(fakeS,Belong[Start[i]],INT_MAX/2,0);
		for(int i=1; i<=b; i++)zkw.AddEdge(BCC+Belong[End[i]],T,INT_MAX/2,0);
		for(int i=1; i<=BCC; i++) {
			zkw.AddEdge(i,BCC+i,1,1);
			zkw.AddEdge(i,BCC+i,INT_MAX/2,0);
		}
		for(int Now=1; Now<=n; Now++)
			for(int Next:edges[Now])
				if(Belong[Now]!=Belong[Next])zkw.AddEdge(BCC+Belong[Now],Belong[Next],INT_MAX/2,0);
		int pre=0;
		do {
			pre=zkw.cost;
			zkw.AddEdge(realS,fakeS,1,0);
			zkw.maxflow(realS,T);
		} while(zkw.cost!=pre);
		if(zkw.cost!=BCC)puts("no solution");
		else printf("%d\n",zkw.cost);
	}
	return 0;
} 
