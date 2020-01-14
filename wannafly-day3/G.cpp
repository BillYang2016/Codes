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

const int maxn=500005;

struct Edge {
	int from,to;
	LL dist;
	Edge(int x=0,int y=0,LL v=0):from(x),to(y),dist(v) {}
};

vector<Edge> edges[maxn];
int n,k,Mark[maxn],From[maxn];
LL Size[maxn],Dist[maxn],Long[maxn],Sec[maxn],Ans[maxn],f[maxn];

void Dfs(int Now,int fa) {
	Size[Now]=Mark[Now];
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs(Next,Now);
		Size[Now]+=Size[Next];
		if(Size[Next]) {
			if(Long[Next]+e.dist>Long[Now]) {
				Sec[Now]=Long[Now];
				Long[Now]=Long[Next]+e.dist;
				From[Now]=Next;
			} else if(Long[Next]+e.dist>Sec[Now])Sec[Now]=Long[Next]+e.dist;
			Dist[Now]+=Dist[Next]+2*e.dist;
		}
	}
}

void TreeDp(int Now,int fa,LL up) {
	f[Now]=max(Long[Now],up);
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Ans[Next]=Ans[Now]+((Size[Next]==0)?2*e.dist:0);
		LL tmp=k-Size[Next]?up+e.dist:0;
		if(From[Now]==Next&&Sec[Now])tmp=max(tmp,Sec[Now]+e.dist);
		else if(From[Now]!=Next&&Long[Now])tmp=max(tmp,Long[Now]+e.dist);
		TreeDp(Next,Now,tmp);
	}
}

void AddEdge(int x,int y,int v) {edges[x].push_back(Edge(x,y,v));}

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	for(int i=1; i<=k; i++)Mark[Get_Int()]=1;
	Dfs(1,0);
	Ans[1]=Dist[1];
	TreeDp(1,0,0);
	for(int i=1; i<=n; i++)printf("%lld\n",Ans[i]-f[i]);
	return 0;
}