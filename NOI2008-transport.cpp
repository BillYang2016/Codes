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

inline const int Get_Int() {
	int num=0,bj=1;
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

const int maxn=65;

int n,m,suc[maxn];
double k,ans=0,c[maxn],f[maxn][maxn][maxn],g[maxn][maxn][maxn],h[maxn],Pow[maxn];
vector<int>edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void TreeDp(int Now,int depth) {
	for(int Next=2; Next<=n; Next++)
		if(suc[Next]==Now)
			TreeDp(Next,depth+1);
	for(int d=min(2,depth); d<=depth; d++) { //不修改
		memset(h,0,sizeof(h));
		for(int Next=2; Next<=n; Next++)
			if(suc[Next]==Now)
				for(int j=m; j>=0; j--)
					for(int k=j; k>=0; k--)
						h[j]=max(h[j],h[k]+g[Next][j-k][d]);
		for(int i=0; i<=m; i++)
			f[Now][i][d]=h[i]+c[Now]*Pow[d];
	}
	if(depth>1) { //修改
		memset(h,0,sizeof(h));
		for(int Next=2; Next<=n; Next++)
			if(suc[Next]==Now)
				for(int j=m; j>=0; j--)
					for(int k=j; k>=0; k--)
						h[j]=max(h[j],h[k]+g[Next][j-k][1]);
		for(int i=1; i<=m; i++)f[Now][i][1]=h[i-1]+c[Now]*k;
	}
	for(int i=0; i<=m; i++)
		for(int d=0; d<depth; d++)
			g[Now][i][d]=max(f[Now][i][d+1],f[Now][i][1]);
}
int main() {
	n=Get_Int();
	m=Get_Int();
	scanf("%lf",&k);
	for(int i=1; i<=n; i++)suc[i]=Get_Int();
	for(int i=1; i<=n; i++)scanf("%lf",&c[i]);
	Pow[0]=1;
	for(int i=1; i<=n; i++)Pow[i]=Pow[i-1]*k;
	for(int now=suc[1],len=2; now!=1; now=suc[now],len++) { //枚举环长
		int tmp=suc[now];
		suc[now]=1;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int root=1; root<=n; root++)
			if(suc[root]==1)TreeDp(root,1);
		memset(h,0,sizeof(h));
		for(int root=1; root<=n; root++)
			if(suc[root]==1)
				for(int j=m; j>=0; j--)
					for(int k=j; k>=0; k--)
						h[j]=max(h[j],h[k]+f[root][j-k][1]);
		double Max=0;
		for(int i=0; i<m; i++)Max=max(Max,h[i]);
		if(tmp==1)Max=max(Max,h[m]); //整个环
		ans=max(ans,(Max+c[1])/(1.0-Pow[len]));
		suc[now]=tmp;
	}
	printf("%0.2lf",ans);
	return 0;
}