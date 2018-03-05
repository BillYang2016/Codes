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

const int maxn=105;

int n,m,K,sum[maxn][maxn],f[maxn][maxn][maxn],g[maxn][maxn][maxn][2],ans=-INT_MAX;

int main() {
	n=Get_Int();
	m=Get_Int();
	K=Get_Int()*2+1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)sum[i][j]=sum[i-1][j]+Get_Int();
	for(int i=1; i<=K; i++)
		for(int j=1; j<=n; j++)f[0][i][j]=g[0][i][j][0]=g[0][i][j][1]=-INT_MAX/2;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			for(int k=1; k<=K; k++) {
				for(int l=i; l>=1; l--)f[j][k][l]=max(f[j-1][k][l],g[j-1][k-1][l][k%2])+sum[i][j]-sum[l-1][j];
				g[j][k][1][0]=g[j][k][i][1]=-INT_MAX/2;
				for(int l=2; l<=i; l++)g[j][k][l][0]=max(g[j][k][l-1][0],f[j][k][l-1]);
				for(int l=i-1; l>=1; l--)g[j][k][l][1]=max(g[j][k][l+1][1],f[j][k][l+1]);
			}
			ans=max(ans,max(f[j][K][i],g[j][K][i][0]));
		}
	printf("%d\n",ans);
	return 0;
}