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

#define lowbit(x) ((x)&(-(x)))

const int maxn=105,maxs=(1<<10)+5; 

int n,m;
LL C[maxn][maxn],edges[maxs],bitnum[maxs],f[maxs][maxn],g[maxs][maxn],cnt[maxs];

void Get_C() {
	C[0][0]=1;
	for(int i=1; i<=m; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=1<<(Get_Int()-1),y=1<<(Get_Int()-1);
		edges[x]|=y;
		edges[y]|=x;
	}
	Get_C();
	bitnum[0]=0;
	for(int i=1; i<(1<<n); i++)bitnum[i]=bitnum[i^lowbit(i)]+1;
	for(int S=1; S<(1<<n); S++) {
		if(bitnum[S]==1) {
			g[S][0]=1;
			continue;
		}
		int u=lowbit(S),v=S^u;
		cnt[S]=cnt[v]+bitnum[edges[u]&v];
		for(int T=(S-1)&S; T; T=(T-1)&S) {
			if(!(T&u))continue;
			for(int i=0; i<=cnt[T]; i++)
				for(int j=0; j<=cnt[S^T]; j++)
					f[S][i+j]+=g[T][i]*C[cnt[S^T]][j];
		}
		for(int i=0; i<=cnt[S]; i++)g[S][i]=C[cnt[S]][i]-f[S][i];
	}
	double ans=0;
	for(int i=0; i<=m; i++)ans+=(double)f[(1<<n)-1][i]/C[cnt[(1<<n)-1]][i];
	printf("%0.6lf\n",ans/(m+1));
	return 0;
} 
