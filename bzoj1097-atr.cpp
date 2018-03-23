#include<bits/stdc++.h>

using namespace std;

#define pii pair<int,int>

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=20005,maxk=25;

struct Edge {int from,to,dist;};

int n,m,K,dist[maxk][maxn],state[maxn],f[1<<20][maxk];
bool vst[maxn];
vector<Edge> edges[maxn];

void Dijkstra(int s) {
	for(int i=1; i<=n; i++)dist[s][i]=INT_MAX/2,vst[i]=0;
	priority_queue<pii,vector<pii>,greater<pii> > Q;
	Q.push(pii(dist[s][s]=0,s));
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(Edge &e:edges[Now]) {
			int Next=e.to;
			if(dist[s][Next]>dist[s][Now]+e.dist) {
				dist[s][Next]=dist[s][Now]+e.dist;
				Q.push(pii(dist[s][Next],Next));
			}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	K=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		edges[x].push_back((Edge) {x,y,v});
		edges[y].push_back((Edge) {y,x,v});
	}
	for(int i=1; i<=K+1; i++)Dijkstra(i);
	int q=Get_Int();
	while(q--) {
		int x=Get_Int(),y=Get_Int();
		state[y]|=1<<(x-2);
	} 
	for(int S=0; S<(1<<K); S++)
		for(int i=1; i<=K+1; i++)
			f[S][i]=INT_MAX/2;
	f[0][1]=0;
	for(int S=0; S<(1<<K); S++)
		for(int i=1; i<=K+1; i++)
			for(int j=2; j<=K+1; j++) {
				int T=S|(1<<(j-2));
				if((T&state[j])==state[j])f[T][j]=min(f[T][j],f[S][i]+dist[i][j]);
			}
	int ans=INT_MAX/2;
	for(int i=1; i<=K+1; i++)ans=min(ans,f[(1<<K)-1][i]+dist[i][n]);
	printf("%d\n",ans);
	return 0;
}