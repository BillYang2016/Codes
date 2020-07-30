#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=55;

int dist[maxn],vst[maxn];
int n,k,Map[maxn][maxn],del[maxn][maxn],from[maxn],ans=0;

#define pii pair<int,int>

void Dijkstra(int s) {
	for(int i=1; i<=n; i++)dist[i]=INT_MAX/2,vst[i]=0;
	priority_queue<pii,vector<pii>,greater<pii> > Q;
	Q.push(pii(dist[s]=0,s));
	while(!Q.empty()) {
		int Now=Q.top().second;
		Q.pop();
		if(vst[Now])continue;
		vst[Now]=1;
		for(int Next=1; Next<=n; Next++) {
			if(del[Now][Next])continue;
			int d=Map[Now][Next];
			if(dist[Next]>dist[Now]+d) {
				dist[Next]=dist[Now]+d;
				from[Next]=Now;
				Q.push(pii(dist[Next],Next));
			}
		}
	}
}

void Dfs(int kth) {
	if(kth==k+1) {
		Dijkstra(1);
		ans=max(ans,dist[n]);
		return;
	}
	Dijkstra(1);
	int tmp[maxn];
	for(int i=1; i<=n; i++)tmp[i]=from[i];
	for(int i=n; i!=1; i=tmp[i]) {
		del[tmp[i]][i]=del[i][tmp[i]]=1;
		Dfs(kth+1);
		del[tmp[i]][i]=del[i][tmp[i]]=0;
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		k=Get_Int();
		ans=0;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)del[i][j]=0;
		for(int i=1; i<=n*(n-1)/2; i++) {
			int u=Get_Int(),v=Get_Int(),w=Get_Int();
			Map[u][v]=Map[v][u]=w;
		}
		Dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}