#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn=505,maxm=150005,maxq=10005;
const LL mod=1e9+7;

LL s[maxm],f[2][maxm],ans[maxq],C[maxn][maxn],fac[maxn],g[maxm];
struct Query {int n,e;} q[maxq];

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int main() {
	int t=Get_Int();
	for(int i=1; i<=t; i++)q[i].n=Get_Int(),q[i].e=Get_Int();
	for(int i=0; i<=500; i++) {
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	fac[0]=1;
	for(int i=1; i<=500; i++)fac[i]=fac[i-1]*i%mod;
	f[0][0]=1;
	int now=0,pre=1;
	for(int i=1; i<=500; i++) {
		swap(now,pre);
		for(int j=0; j<=i*(i-1)/2; j++) {
			s[j]=(f[pre][j]+(j?s[j-1]:0))%mod;
			f[now][j]=(s[j]-(j>=i?s[j-i]:0)+mod)%mod;
			g[j]=(f[now][j]+(j?g[j-1]:0))%mod;
		}
		for(int j=1; j<=t; j++)if(q[j].n>=i) {
			int n=q[j].n,e=min(q[j].e,i*(i-1)/2);
			ans[j]=(ans[j]+g[e]*C[n][i]%mod*C[n][i]%mod*(n-i+1)%mod*fac[n-i]%mod*fac[n-i]%mod)%mod;
		}
	}
	for(int i=1; i<=t; i++)printf("%lld\n",ans[i]);
	return 0;
}