#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define lowbit(x) (x&(-x))

const int maxn=20,maxs=1<<16,mod=1e9+7;

int n,a[maxn][maxn],f[maxs],g[maxs];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			a[i][j]=Get_Int();
	for(int S=1; S<(1<<n); S++) {
		g[S]=1;
		for(int i=1; i<=n; i++)if(S&(1<<(i-1)))
			for(int j=i+1; j<=n; j++)if(S&(1<<(j-1)))
				g[S]=1ll*g[S]*(a[i][j]+1)%mod;
		f[S]=g[S];
		int u=S^lowbit(S);
		for(int T=u; T; T=(T-1)&u)f[S]=(f[S]-1ll*g[T]*f[S^T]%mod+mod)%mod;
	}
	printf("%d\n",f[(1<<n)-1]);
	return 0;
}