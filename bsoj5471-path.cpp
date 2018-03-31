#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

struct Edge {
	int from,to,dist,id;
	Edge(int x=0,int y=0,int v=0,int i=0):from(x),to(y),dist(v),id(i) {}
	bool operator < (const Edge &b) const {return from<b.from||(from==b.from&&to>b.to);}
} edge[maxm];

vector<Edge> edges[maxn];

void Dfs(int Now) {
	vst[Now]=1;
	for(Edge &e:edges[Now])if(!vst[e.to])Dfs(e.to);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		edge[i]=Edge(x,y,v,i);
		edges[x].push_back(edge[i]);
	}
	Dfs(0);
	for(int i=1; i<=n; i++)if(!vst[i])del[a[i]]=0;
	sort(edge+1,edge+m+1);

	return 0;
}