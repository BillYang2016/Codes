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
#include<set>
using namespace std;

typedef long long LL;

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
	int from,to;
	LL dist;
};

int n,m,Depth[maxn],father[maxn],Size[maxn],Son[maxn],Dfn[maxn],M[maxn],Top[maxn],step=0;
LL Dist[maxn],ans=0;
bool a[maxn];
vector<Edge> edges[maxn];

void AddEdge(int x,int y,LL v) {
	edges[x].push_back((Edge) {x,y,v});
}

void Dfs(int Now,int fa,int depth,LL dist) {
	Depth[Now]=depth;
	Dist[Now]=dist;
	father[Now]=fa;
	Size[Now]=1;
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1,dist+e.dist);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Dfs2(int Now,int top) {
	Top[Now]=top;
	Dfn[Now]=++step;
	M[step]=Now;
	if(Son[Now])Dfs2(Son[Now],top);
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
}

int LCA(int x,int y) {
	for(; Top[x]!=Top[y]; x=father[Top[x]])if(Depth[Top[x]]<Depth[Top[y]])swap(x,y);
	return Depth[x]<Depth[y]?x:y;
}

int dist(int x,int y) {
	return Dist[x]+Dist[y]-(Dist[LCA(x,y)]<<1);
}

set<int> S;

void modify(int x,int delta) {
	if(delta==1)S.insert(Dfn[x]);
	int pre=0,suc=0;
	auto it=S.find(Dfn[x]),it2=it;
	if(it!=S.begin())pre=M[*--it];
	if(++it2!=S.end())suc=M[*it2];
	if(pre)ans+=dist(pre,x)*delta;
	if(suc)ans+=dist(x,suc)*delta;
	if(pre&&suc)ans+=dist(pre,suc)*delta*-1;
	if(delta==-1)S.erase(Dfn[x]);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	Dfs(1,-1,1,0);
	Dfs2(1,1);
	for(int i=1; i<=m; i++) {
		int x=Get_Int();
		if(a[x])modify(x,-1);
		else modify(x,1);
		a[x]^=1;
		if(S.empty())puts("0");
		else printf("%lld\n",ans+dist(M[*S.begin()],M[*--S.end()]));
	}
	return 0;
}
