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

const int maxn=100005;

struct Edge {
	int from,to,dist;
};

int n,m,root,Degree[maxn];
double f[maxn],d[maxn];
bool onCircle[maxn];
vector<Edge> edges[maxn];

void AddEdge(int x,int y,int v) {
	edges[x].push_back((Edge) {x,y,v});
}

void Dfs1(int Now,int father) {
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==father||onCircle[Next])continue;
		Degree[Now]++;
		Dfs1(Next,Now);
		d[Now]+=f[Next]+e.dist;
	}
	if(Degree[Now])f[Now]=d[Now]/Degree[Now];
	if(Now!=root)Degree[Now]++;
}

void Dfs2(int Now,int father) {
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==father||onCircle[Next])continue;
		d[Next]+=(d[Now]-f[Next]-e.dist)/max(1,Degree[Now]-1)+e.dist;
		Dfs2(Next,Now);
	}
}

namespace Tree {
	void solve() {
		root=1;
		Dfs1(1,0);
		Dfs2(1,0);
	}
}

namespace CircleAndTree {
	int Dfn[maxn],father[maxn],step=0;
	double g[maxn],h[maxn];
	bool bj=0;
	void Find_Circle(int Now) {
		Dfn[Now]=++step;
		for(Edge& e:edges[Now]) {
			int Next=e.to;
			if(!Dfn[Next]) {
				father[Next]=Now;
				Find_Circle(Next);
			} else if(father[Now]!=Next&&Dfn[Next]<Dfn[Now]) {
				onCircle[Next]=1;
				while(Now!=Next) {
					onCircle[Now]=1;
					Now=father[Now];
				}
				bj=1;
				return;
			}
			if(bj)return;
		}
	}
	void Dfs(int Now,int father) {
		bool bj=0;
		g[Now]=0;
		for(Edge& e:edges[Now]) {
			int Next=e.to;
			if(Next==root||Next==father||!onCircle[Next])continue;
			bj=1;
			Dfs(Next,Now);
			g[Now]+=g[Next]+e.dist;
		}
		if(Now==root)return;
		if(!bj)g[Now]=d[Now]/max(Degree[Now],1);
		else g[Now]=(g[Now]+d[Now])/(Degree[Now]+1);
	}
	void solve() {
		Find_Circle(1);
		for(int i=1; i<=n; i++)
			if(onCircle[i]) {
				root=i;
				Dfs1(i,0);
			}
		for(int i=1; i<=n; i++)
			if(onCircle[i]) {
				root=i;
				Dfs(i,0);
				h[i]=g[i];
			}
		for(int i=1; i<=n; i++)
			if(onCircle[i]) {
				Degree[i]+=2;
				d[i]+=h[i];
			}
		for(int i=1; i<=n; i++)
			if(onCircle[i])Dfs2(i,0);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	if(m==n-1)Tree::solve();
	else CircleAndTree::solve();
	double ans=0;
	for(int i=1; i<=n; i++)ans+=d[i]/Degree[i];
	printf("%0.5lf\n",ans/n);
	return 0;
} 
