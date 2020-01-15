#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005,K=22;

typedef long long LL;

int n,m,Depth[maxn],p[maxn][K];
LL f[maxn],a[maxn],b[maxn];
vector<int> edges[maxn];

void Dfs(int Now,int fa,int depth) {
	Depth[Now]=depth;
	p[Now][0]=fa;
	int K=log2(Depth[Now]);
	for(int i=1; i<=K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1);
	}
}

int LCA(int x,int y) {
	if(Depth[x]<Depth[y])swap(x,y);
	for(int i=K-1; i>=0; i--)
		if(Depth[x]==Depth[y])break;
		else if(Depth[x]-(1<<i)>=Depth[y])x=p[x][i];
	if(x==y)return y;
	for(int i=K-1; i>=0; i--)
		if(p[x][i]&&p[x][i]!=p[y][i]) {
			x=p[x][i];
			y=p[y][i];
		}
	return p[x][0];
}

void Dfs1(int Now) {
	for(int Next:edges[Now]) {
		if(Next==p[Now][0])continue;
		Dfs1(Next);
		a[Now]+=a[Next];
		b[Now]+=b[Next];
	}
}

void Dfs2(int Now) {
	f[Now]+=a[Now]*Depth[Now]+b[Now];
	for(int Next:edges[Now]) {
		if(Next==p[Now][0])continue;
		f[Next]+=f[Now];
		Dfs2(Next);
	}
}

void AddEdge(int x,int y) {edges[x].push_back(y);}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Dfs(1,0,1);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),lca=LCA(x,y),len=Depth[x]+Depth[y]-2*Depth[lca],lenl=Depth[x]-Depth[lca];
		a[x]-=2;
		a[y]-=2;
		a[lca]+=4;
		b[x]+=1-len+2*Depth[x];
		b[y]+=1-len+2*Depth[y];
		b[lca]-=1-len+2*Depth[x]+1-len+2*Depth[y];
		f[1]+=1ll*lenl*(len-lenl);
	}
	Dfs1(1);
	Dfs2(1);
	for(int i=1; i<=n; i++)printf("%lld\n",f[i]);
	return 0;
}