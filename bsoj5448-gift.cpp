#include<bits/stdc++.h>

using namespace std;

namespace FastIO {
	const int L=1<<15;
	char buffer[L],*S,*T;
	/*inline char getchar() {
		if(S==T) {T=(S=buffer)+fread(buffer,1,L,stdin);if(S==T)return EOF;}
		return *S++;
	}*/
	inline int Get_Int() {
		int num=0,bj=1;
		char x=getchar();
		while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
		while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
		return num*bj;
	}
}

using FastIO::Get_Int;

const int maxn=4005;

struct Edge {
	int from,to,cap,flow;
	Edge(int x=0,int y=0,int c=0,int f=0):from(x),to(y),cap(c),flow(f) {}
};

struct Dinic {
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
	int AddEdge(int x,int y,int v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
		return m-2;
	}
	bool bfs() {
		fill(vst+1,vst+n+1,0);
		queue<int>Q;
		Q.push(t);
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
		if(Now==t||!a)return a;
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
				if(!a)break;
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

int n,m,a[maxn],b[200005],p[200005],q[200005],s[maxn],link[maxn],S,T,sum=0;

void build() {
	S=n+1,T=n+2;
	dinic.init(T);
	for(int i=1; i<=m; i++) {
		dinic.AddEdge(p[i],q[i],b[i]);
		dinic.AddEdge(q[i],p[i],b[i]);
		s[p[i]]+=b[i],s[q[i]]+=b[i];
	}
	for(int i=1; i<=n; i++)link[i]=dinic.AddEdge(i,T,2*a[i]);
	for(int i=1; i<=n; i++)dinic.AddEdge(S,i,s[i]);
}

bool Check(int mid) {
	for(auto &e:dinic.edges)e.flow=0;
	for(int i=1; i<=n; i++)dinic.edges[link[i]].cap=2*mid*a[i];
	return sum-dinic.maxflow(S,T)>0;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		p[i]=Get_Int();
		q[i]=Get_Int();
		b[i]=Get_Int();
		sum+=2*b[i];
	}
	build();
	int Left=0,Right=sum;
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(Check(mid))Left=mid+1;
		else Right=mid-1;
	}
	printf("%d\n",Right);
	return 0;
}