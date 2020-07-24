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

const int maxn=2e4+5,maxk=25;

struct Edge {
	int to,a,b;
	Edge(int y,int _a,int _b):to(y),a(_a),b(_b) {}
};

vector<Edge> edges[maxn];

LL f[maxn][maxk],g[maxk],x;
int K,Size[maxn];

void Dfs(int Now,int fa) {
	memset(f[Now],0x3f,sizeof(f[Now]));
	Size[Now]=1;
	f[Now][0]=0;
	for(Edge& e:edges[Now]) {
		int Next=e.to,a=e.a,b=e.b;
		if(Next==fa)continue;
		Dfs(Next,Now);
		memset(g,0x3f,sizeof(g));
		for(int k=0; k<=min(K,Size[Now]); k++)
			for(int d=0; d+k<=K&&d<=Size[Next]; d++) {
				if(f[Now][k]+f[Next][d]+b<=x)g[k+d]=min(g[k+d],max(f[Now][k],f[Next][d]+b));
				if(f[Now][k]+f[Next][d]+a<=x&&d+k+1<=K)g[k+d+1]=min(g[k+d+1],max(f[Now][k],f[Next][d]+a));
			}
		Size[Now]+=Size[Next];
		for(int k=0; k<=K; k++)f[Now][k]=g[k];
	}
}

int main() {
	int t=Get_Int();
	while(t--) {
		int n=Get_Int(),k=Get_Int();
		for(int i=1; i<=n; i++)edges[i].clear();
		K=k;
		for(int i=1; i<n; i++) {
			int u=Get_Int(),v=Get_Int(),a=Get_Int(),b=Get_Int();
			edges[u].push_back(Edge(v,a,b));
			edges[v].push_back(Edge(u,a,b));
		}
		LL Left=0,Right=2e14;
		while(Left<=Right) {
			LL mid=(Left+Right)>>1;
			x=mid;
			Dfs(1,0);
			if(f[1][k]<=mid)Right=mid-1;
			else Left=mid+1;
		}
		printf("%lld\n",Left);
	}
	return 0;
}