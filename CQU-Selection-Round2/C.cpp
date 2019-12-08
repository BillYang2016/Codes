#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;
int n,q,p[maxn][35],f[maxn][35],a[maxn],father[maxn],Depth[maxn];
vector<int>edges[maxn];

void AddEdge(int x,int y) {edges[x].push_back(y);}

void Sparse_Table() {
	for(int i=1; i<=n; i++)
		for(int j=0; j<=log2(n); j++)p[i][j]=-1;
	for(int i=1; i<=n; i++)p[i][0]=father[i];
	for(int j=1; j<=log2(n); j++)
		for(int i=1; i<=n; i++)
			if(p[i][j-1]!=-1)p[i][j]=p[p[i][j-1]][j-1];
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	int k=log2(Depth[a]);
	for(int i=k; i>=0; i--) {
		if(Depth[a]==Depth[b])break;
		if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	}
	if(a==b)return b;
	for(int i=k; i>=0; i--)
		if(p[a][i]!=-1&&p[a][i]!=p[b][i]) {
			a=p[a][i];
			b=p[b][i];
		}
	return p[a][0];
}

void Dfs(int Now,int depth) {
	Depth[Now]=depth;
	for(int i=0; i<edges[Now].size(); i++) {
		int Next=edges[Now][i];
		if(Next==father[Now])continue;
		father[Next]=Now;
		Dfs(Next,depth+1);
	}
}

void Sparse_Table2() {
	for(int i=1; i<n; i++)f[i][0]=a[i];
	for(int j=1; (1<<j)<n; j++)
		for(int i=1; i+(1<<j)-1<n; i++) {
			int L=f[i][j-1],R=f[i+(1<<(j-1))][j-1];
			if(Depth[L]<Depth[R])f[i][j]=L;
			else f[i][j]=R;
		}
}

int Query(int Left,int Right) {
	int x=log2(Right-Left+1);
	int L=f[Left][x],R=f[Right-(1<<x)+1][x];
	if(Depth[L]<Depth[R])return L;
	else return R;
}

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	father[1]=-1;
	Dfs(1,1);
	Sparse_Table();
	for(int i=1; i<n; i++)a[i]=LCA(i,i+1);
	Sparse_Table2();
	q=Get_Int();
	for(int i=1; i<=q; i++) {
		int x=Get_Int(),y=Get_Int();
		if(x==y)printf("%d\n",x);
		else printf("%d\n",Query(x,y-1));
	}
	return 0;
}