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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=200005;

struct Edge {
	int from,to;
	LL dist;
};

int n,m,T;
LL dist[maxn];
bool vst[maxn];
vector<Edge> edges[maxn];

void AddEdge(int x,int y,LL v) {
	edges[x].push_back((Edge) {x,y,v});
}

#define pii pair<LL,int>
#define mp make_pair

void Dijkstra() {
	priority_queue<pii,vector<pii>,greater<pii> >Q;
	for(int i=1; i<=T; i++)dist[i]=LLONG_MAX;
	dist[T]=0;
	Q.push(mp(0,T));
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(Edge& e:edges[Now]) {
			int Next=e.to;
			if(dist[Next]>dist[Now]+e.dist) {
				dist[Next]=dist[Now]+e.dist;
				Q.push(mp(dist[Next],Next));
			}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	T=n+1;
	for(int i=1; i<=m; i++) {
		LL x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v*2);
		AddEdge(y,x,v*2);
	}
	for(int i=1; i<=n; i++)AddEdge(T,i,Get_Int());
	Dijkstra();
	for(int i=1; i<=n; i++)printf("%I64d ",dist[i]);
	return 0;
}