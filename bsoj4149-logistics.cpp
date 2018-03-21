#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=205;

int n,k,a[maxn],f[maxn][maxn],dist[maxn][maxn];
vector<int> edges[maxn];

void Dfs(int root,int Now,int fa,int depth) {
	dist[root][Now]=depth;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs(root,Next,Now,depth+1);
	}
}

void Dp(int Now,int fa) {
	for(int i=1; i<=n; i++)f[Now][i]=a[dist[Now][i]];
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dp(Next,Now);
		int Min=INT_MAX;
		for(int j=1; j<=n; j++)Min=min(Min,f[Next][j]+k);
		for(int j=1; j<=n; j++)f[Now][j]+=min(Min,f[Next][j]);
	}
}

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=1; i<n; i++)a[i]=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	for(int i=1; i<=n; i++)Dfs(i,i,0,0);
	Dp(1,0);
	int ans=INT_MAX;
	for(int i=1; i<=n; i++)ans=min(ans,f[1][i]+k);
	printf("%d\n",ans);
	return 0;
}