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

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=200005,MAX_BASE=60;

struct Linear_Bases {
	LL b[MAX_BASE+5];
	void build(vector<LL> a) {
		for(LL num:a)
			for(int j=MAX_BASE; j>=0; j--)
				if(num>>j&1) {
					if(b[j]) { //该位存在基
						num^=b[j];
						continue;
					}
					b[j]=num;
					for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
					for(int k=j+1; k<=MAX_BASE; k++)if(b[k]>>j&1)b[k]^=b[j];
					break;
				}
	}
} lb;

struct Edge {
	int from,to;
	LL dist;
	Edge(int x=0,int y=0,LL v=0):from(x),to(y),dist(v) {}
};

vector<Edge>edges[maxn];
vector<LL>a;
int n,m,vst[maxn];
LL Dist[maxn];

void AddEdge(int x,int y,LL v) {
	edges[x].push_back(Edge(x,y,v));
}

void Dfs(int Now) {
	vst[Now]=1;
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		LL dist=e.dist;
		if(!vst[Next]) {
			Dist[Next]=Dist[Now]^dist;
			Dfs(Next);
		} else a.push_back(Dist[Now]^Dist[Next]^dist);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		LL v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	Dfs(1);
	lb.build(a);
	LL ans=Dist[n];
	for(int i=MAX_BASE; i>=0; i--)ans=max(ans,ans^lb.b[i]);
	printf("%lld\n",ans);
	return 0;
} 
