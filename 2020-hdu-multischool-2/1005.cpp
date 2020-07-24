#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=6005;

struct Edge {
	int from,to,cap,flow;
	LL cost;
	Edge(int x=0,int y=0,int c=0,int f=0,LL co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

struct zkw_CostFlow {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn],vst[maxn];
	LL dist[maxn];
	LL flow,cost;
	void init(int n) {
		flow=cost=0;
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,int v,LL f) {
		edges.push_back(Edge(x,y,v,0,f));
		edges.push_back(Edge(y,x,0,0,-f));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool spfa() {
		memset(dist,0x3f,sizeof(dist));
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
		return dist[s]<0x3f3f3f3f3f3f3f3f;
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

int discretization(int n,int *a) {
	sort(a+1,a+n+1);
	int tot=unique(a+1,a+n+1)-a-1;
	return tot;
}

LL a[maxn],b[maxn],c[maxn];
int d[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int(),m=Get_Int(),cnt=0;
		for(int i=1; i<=n; i++) {
			a[i]=Get_Int(),b[i]=Get_Int(),c[i]=Get_Int();
			LL x=-b[i]/(2*a[i]);
			int Left=max(1ll,x-n-1),Right=min(x+n+1,(LL)m);
			if(Right-Left+1<=n) {
				if(Left==1)Right=min(m,Right+n-(Right-Left+1));
				else Left=max(1,Left-(n-(Right-Left+1)));
			}
			for(int j=Left; j<=Right; j++)d[++cnt]=j;
		}
		int tot=discretization(cnt,d);
		zkw.init(n+tot+4);
		int S=n+tot+1,T=n+tot+2,SS=T+1,TT=SS+1;
		for(int i=1; i<=n; i++) {
			LL x=-b[i]/(2*a[i]);
			int Left=max(1ll,x-n-1),Right=min(x+n+1,(LL)m);
			if(Right-Left+1<=n) {
				if(Left==1)Right=min(m,Right+n-(Right-Left+1));
				else Left=max(1,Left-(n-(Right-Left+1)));
			}
			for(int j=Left; j<=Right; j++) {
				int to=lower_bound(d+1,d+tot+1,j)-d;
				zkw.AddEdge(i,n+to,1,a[i]*j*j+b[i]*j+c[i]);
			}
		}
		for(int i=1; i<=n; i++)zkw.AddEdge(S,i,1,0);
		for(int i=1; i<=tot; i++)zkw.AddEdge(n+i,T,1,0);
		for(int k=1; k<=n; k++) {
			zkw.AddEdge(SS,S,1,0);
			zkw.AddEdge(T,TT,1,0);
			zkw.maxflow(SS,TT);
			printf("%lld%c",zkw.cost,k==n?'\n':' ');
		}
	}
	return 0;
}