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

const int maxn=100005,K=20;

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
	bool operator < (const Edge &b) const {return dist>b.dist;}
};

vector<Edge> edges,tree[maxn];
int n,m,q,father[maxn],rk[maxn],id[maxn],train[maxn],Depth[maxn],p[maxn][K];
LL a[maxn],f[maxn][K];

void Dfs(int Now,int fa,int depth,int dist) {
	Depth[Now]=depth;
	p[Now][0]=fa;
	f[Now][0]=dist;
	for(int i=1; i<K; i++) {
		p[Now][i]=p[p[Now][i-1]][i-1];
		f[Now][i]=min(f[Now][i-1],f[p[Now][i-1]][i-1]);
	}
	for(Edge &e:tree[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1,e.dist);
	}
}

int Get_Father(int x) {return father[x]==x?x:father[x]=Get_Father(father[x]);}

LL Minval(int x,int y) {
	x=id[x],y=id[y];
	if(x==y)return LLONG_MAX;
	LL Min=LLONG_MAX;
	if(Depth[x]<Depth[y])swap(x,y);
	for(int i=K-1; i>=0; i--)if(Depth[x]-(1<<i)>=Depth[y])Min=min(Min,f[x][i]),x=p[x][i];
	if(x==y)return Min;
	for(int i=K-1; i>=0; i--)if(p[x][i]!=p[y][i])Min=min(Min,min(f[x][i],f[y][i])),x=p[x][i],y=p[y][i];
	return min(Min,min(f[x][0],f[y][0]));
}

int main() {
	n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)rk[i]=Get_Int(),id[i]=father[i]=i;
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		edges.push_back(Edge(x,y,v));
	}
	int Min=n,cnt=n;
	for(int i=1; i<=q; i++)train[i]=Get_Int(),Min=min(Min,train[i]);
	for(int i=1; i<=q; i++)id[train[i]]=Min,cnt--;
	sort(edges.begin(),edges.end());
	for(Edge &e:edges) {
		int fx=Get_Father(id[e.from]),fy=Get_Father(id[e.to]);
		if(fx==fy)continue;
		father[fx]=fy;
		tree[id[e.from]].push_back(Edge(id[e.from],id[e.to],e.dist));
		tree[id[e.to]].push_back(Edge(id[e.to],id[e.from],e.dist));
		if(--cnt==0)break;
	}
	Dfs(1,0,0,0);
	LL left=0;
	if(a[rk[1]]>=0)left+=a[rk[1]];
	else puts("0");
	for(int i=2; i<=n; i++) {
		if(a[rk[i]]>=0)left=min(left,Minval(rk[i-1],rk[i]))+a[rk[i]];
		else {
			left=min(left,Minval(rk[i-1],rk[i]));
			LL sell=min(left,-a[rk[i]]);
			printf("%lld\n",sell);
			left-=sell;
		}
	}
	return 0;
}