#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Dist {
	int fir,sec;
	Dist(int x=0,int y=0):fir(x),sec(y) {}
	bool operator < (const Dist &b) const {return (sec>b.sec||(sec==b.sec&&fir>b.fir));}
} dist[maxn];

struct Edge {int from,to,dist;};

int n,m,k;
vector<Edge> edges[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int()+1,y=Get_Int()+1,v=Get_Int();
		edges[x].push_back((Edge) {x,y,v});
		edges[y].push_back((Edge) {y,x,v});
	}
	priority_queue<pii> Q;
	for(int i=1; i<=k; i++) {
		int x=Get_Int()+1;
		Q.push(pii(dist[x]=Dist(0,0),x));
	}
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(Edge &e:edges[Now]) {
			int Next=e.to;
			if(dist[Next].fir>dis[Now].sec+e.dist) {
				dist[Next].sec=dist[Next].fir;
				dist[Next].fir=dist[Now].sec+e.dist;
				Q.push(dist[Next],Next);
			} else if(dist[Next].sec>dist[Now].sec+e.dist) {
				dist[Next].sec=dist[Now].sec+e.dist;
				Q.push(dist[Next],Next);
			}
		}
	}
	printf("%d\n",dist[1].sec);
	return 0;
}