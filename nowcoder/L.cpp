#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=1025;

struct Edge {
	int from,to;
	LL cap,flow;
	Edge(int x=0,int y=0,LL c=0,LL f=0):from(x),to(y),cap(c),flow(f) {}
};

struct Dinic {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool vst[maxn];
	LL dist[maxn];
	int cur[maxn];
	void init(int n) {this->n=n;}
	int AddEdge(int x,int y,LL v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
		return m-1;
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
			flow+=dfs(s,LLONG_MAX/2);
		}
		return flow;
	}
} dinic;

int n,m,cnt[maxn],num[10];

int main() {
	n=Get_Int();
	m=Get_Int();
	dinic.init(n+9);
	int S=n+8,T=n+9;
	LL sum=0;
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		dinic.AddEdge(i+7,T,x);
		sum+=x;
		cnt[i]=Get_Int();
		for(int j=1; j<=cnt[i]; j++)dinic.AddEdge(Get_Int(),i+7,INT_MAX/2);
	}
	for(int i=1; i<=7; i++)num[i]=dinic.AddEdge(S,i,0);
	LL Left=1,Right=sum*7;
	while(Left<=Right) {
		LL mid=(Left+Right)>>1;
		for(auto &e:dinic.edges)e.flow=0;
		for(int i=1; i<=7; i++)dinic.edges[num[i]].cap=dinic.edges[num[i]^1].cap=(mid/7+(i<=mid%7))*m;
		LL x=dinic.maxflow(S,T);
		if(x==sum)Right=mid-1;
		else Left=mid+1;
	}
	printf("%lld\n",Left);
	return 0;
}