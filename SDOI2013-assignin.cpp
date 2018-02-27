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

const int maxn=705,mod1=999599,mod2=999997;

struct Edge {
	int from,to,cap,flow,cost;
	Edge(int x=0,int y=0,int c=0,int f=0,int co=0):from(x),to(y),cap(c),flow(f),cost(co) {}
};

struct zkw_CostFlow {
	const static int maxn=55;
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool inque[maxn],vst[maxn];
	int dist[maxn];
	int flow,cost;
	void init(int n) {
		this->n=n;
		edges.clear();
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
		flow=cost=0;
		while(spfa()) {
			memset(vst,0,sizeof(vst));
			flow+=dfs(s,INT_MAX);
		}
		return flow;
	}
} zkw;

int BASE1,BASE2,POW1,POW2;
int n,Size[maxn],father[maxn],x[maxn],y[maxn],A[maxn],B[maxn],root,f[maxn][maxn];
vector<int> edges[maxn],Center;

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Dfs(int Now,int fa) {
	Size[Now]=1;
	bool bj=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now);
		Size[Now]+=Size[Next];
		bj&=Size[Next]<=(n>>1);
	}
	bj&=(n-Size[Now])<=(n>>1);
	if(bj)Center.push_back(Now);
}

struct node {
	int id,depth,hash1,hash2;
	bool operator < (const node& b) const {
		return depth>b.depth||(depth==b.depth&&hash1<b.hash1)||(depth==b.depth&&hash1==b.hash1&&hash2<b.hash2);
	}
	bool operator != (const node& b) const {
		return depth!=b.depth||hash1!=b.hash1||hash2!=b.hash2;
	}
} a[maxn];

void Get_Hash(int Now,int fa,int depth) {
	father[Now]=fa;
	Size[Now]=0;
	a[Now].id=Now;
	a[Now].depth=depth;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Get_Hash(Next,Now,depth+1);
		Size[Now]++;
	}
	vector<int> son1,son2;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		son1.push_back(a[Next].hash1);
		son2.push_back(a[Next].hash2);
	}
	if(son1.empty()) {
		a[Now].hash1=BASE1,a[Now].hash2=BASE2;
		return;
	}
	sort(son1.begin(),son1.end()),sort(son2.begin(),son2.end());
	for(int i=0; i<son1.size(); i++) {
		a[Now].hash1=(a[Now].hash1*BASE1+son1[i]*POW1)%mod1;
		a[Now].hash2=(a[Now].hash2*BASE2+son2[i]*POW2)%mod2;
	}
}

int main() {
	srand(99995999);
	BASE1=rand()%500+1,BASE2=rand()%500+1,POW1=rand()%500+1,POW2=rand()%500+1;
	n=Get_Int();
	for(int i=1; i<n; i++) {
		x[i]=Get_Int();
		y[i]=Get_Int();
		AddEdge(x[i],y[i]),AddEdge(y[i],x[i]);
	}
	for(int i=1; i<=n; i++)A[i]=Get_Int();
	for(int i=1; i<=n; i++)B[i]=Get_Int();
	Dfs(1,0);
	if(Center.size()>1) {
		for(int i=1; i<=n; i++)edges[i].clear();
		for(int i=1; i<n; i++) {
			if((x[i]==Center[0]&&y[i]==Center[1])||(x[i]==Center[1]&&y[i]==Center[0]))continue;
			AddEdge(x[i],y[i]),AddEdge(y[i],x[i]);
		}
		root=++n;
		AddEdge(n,Center[0]),AddEdge(Center[0],n);
		AddEdge(n,Center[1]),AddEdge(Center[1],n);
	} else root=Center[0];
	Get_Hash(root,0,1);
	sort(a+1,a+n+1);
	memset(f,-1,sizeof(f));
	for(int i=2,j=1; i<=n+1; i++)
		if(i==n+1||a[i]!=a[i-1]) {
			int tmp=j;
			for(; j<i; j++)
				for(int k=tmp; k<i; k++) {
					zkw.init(Size[a[j].id]+Size[a[k].id]+2);
					int cntj=1,cntk=1,delta=Size[a[j].id];
					for(int Nextj:edges[a[j].id]) {
						if(Nextj==father[a[j].id])continue;
						cntk=1;
						for(int Nextk:edges[a[k].id]) {
							if(Nextk==father[a[k].id])continue;
							if(~f[Nextj][Nextk])zkw.AddEdge(cntj,cntk+delta,1,f[Nextj][Nextk]);
							cntk++;
						}
						cntj++;
					}
					int S=Size[a[j].id]+Size[a[k].id]+1,T=S+1;
					cntj=1;
					for(int Nextj:edges[a[j].id]) {
						if(Nextj==father[a[j].id])continue;
						zkw.AddEdge(S,cntj++,1,0);
					}
					cntk=1;
					for(int Nextk:edges[a[k].id]) {
						if(Nextk==father[a[k].id])continue;
						zkw.AddEdge((cntk++)+delta,T,1,0);
					}
					zkw.maxflow(S,T);
					f[a[j].id][a[k].id]=zkw.cost+(A[a[j].id]^B[a[k].id]);
				}
			j=i;
		}
	printf("%d\n",f[root][root]);
	return 0;
} 
