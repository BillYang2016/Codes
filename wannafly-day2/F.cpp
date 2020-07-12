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

const int maxn=1000005;

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
};

LL Size[maxn],Value[maxn],restf[maxn];
int n,step=0,root=1,father[maxn],Son[maxn],Top[maxn],First[maxn],Last[maxn];
vector<Edge> edges[maxn];

void Dfs(int Now,int fa) {
	Size[Now]=1;
	father[Now]=fa;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Value[Next]=e.dist;
		Dfs(Next,Now);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Dfs(int Now,int fa,int top) {
	Top[Now]=top;
	First[Now]=++step;
	if(Son[Now])Dfs(Son[Now],Now,top);
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa||Next==Son[Now])continue;
		Dfs(Next,Now,Next);
	}
	Last[Now]=step;
}

void AddEdge(int x,int y,int v) {edges[x].push_back(Edge(x,y,v));}

struct BIT {
	LL c[maxn];
	#define lowbit(x) (x&(-x))
	void add(int x,int v) {
		for(int i=x; i<=n; i+=lowbit(i))c[i]+=v;
	}
	LL query(int x) {
		LL ans=0;
		for(int i=x; i>=1; i-=lowbit(i))ans+=c[i];
		return ans;
	}
} bit;

LL Query(int x) {return bit.query(Last[x])-bit.query(First[x]-1);}

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	Dfs(1,0);
	Dfs(1,0,1);
	int q=Get_Int();
	LL sum=0;
	while(q--) {
		int opt=Get_Int();
		if(opt==1) {
			int x=Get_Int(),v=Get_Int();
			for(int i=Top[x]; i!=1; i=Top[father[i]])restf[father[i]]+=v*Value[i];
			bit.add(First[x],v);
			sum+=v;
		} else root=Get_Int();
		printf("%lld\n",restf[root]+Query(Son[root])*Value[Son[root]]+(sum-Query(root))*Value[root]);
	}
	return 0;
}