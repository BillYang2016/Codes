#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=255;

int n,m,k,My[maxn],a[maxn][maxn];
bool vst[maxn];
vector<int> edges[maxn];

bool Dfs(int Now) {
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		vst[Next]=1;
		if(!My[Next]||Dfs(My[Next])) {
			My[Next]=Now;
			return true;
		}
	}
	return false;
}

bool Check(int lim) {
	for(int i=1; i<=n; i++)edges[i].clear();
	for(int i=1; i<=m; i++)My[i]=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(a[i][j]<=lim)edges[i].push_back(j);
	int ans=0;
	for(int i=1; i<=n; i++) {
		memset(vst,0,sizeof(vst));
		if(Dfs(i))ans++;
	}
	return ans>=n-k+1;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	int Left=1,Right=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			a[i][j]=Get_Int(),Right=max(Right,a[i][j]);
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(Check(mid))Right=mid-1;
		else Left=mid+1;
	}
	printf("%d\n",Left);
	return 0;
}