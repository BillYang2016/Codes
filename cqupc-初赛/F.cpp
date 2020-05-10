#include<bits/stdc++.h>

using namespace std;

const int mod=998244353;

int n,K,l,r,f[100005][15];

int Cal(int x) {
	if(l-1-x<0)return ((r-x)/K+1)%mod;
	return (((r-x)/K)%mod-((l-1-x)/K)%mod+mod)%mod;
}

int main() {
	scanf("%d%d%d%d",&n,&K,&l,&r);
	f[0][0]=1;
	for(int i=1; i<=n; i++)
		for(int j=0; j<K; j++)
			for(int k=0; k<K; k++)
				f[i][(j+k)%K]=(f[i][(j+k)%K]+1ll*f[i-1][j]*Cal(k)%mod)%mod;
	printf("%d\n",f[n][0]);
	return 0;
}