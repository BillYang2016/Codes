#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005;
const LL mod=1e9+7;

int n;
LL fac[maxn],invf[maxn],d[maxn],g[maxn],ans=0;

void add(LL &x,LL v) {x+=v;if(x>=mod)x-=mod;}

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

int main() {
	n=Get_Int();
	fac[0]=1;
	for(int i=1; i<=n; i++)fac[i]=fac[i-1]*i%mod;
	invf[n]=Quick_Pow(fac[n],mod-2);
	for(int i=n; i>=1; i--)invf[i-1]=invf[i]*i%mod;
	d[0]=d[2]=1;
	for(int i=3; i<=n; i++)d[i]=(i-1)*(d[i-2]+d[i-1])%mod;
	for(int i=2; i<=n; i++) {
		g[0]=1;
		for(int j=1; i*j<=n; j++) {
			int k=i*j;
			g[j]=g[j-1]*fac[k-1]%mod*invf[i-1]%mod*invf[k-i]%mod*fac[i-1]%mod;
			LL tmp=fac[n]*invf[k]%mod*invf[n-k]%mod*g[j]%mod*d[n-k]%mod;
			if(j&1)add(ans,tmp);
			else add(ans,mod-tmp);
		}
	}
	printf("%lld\n",ans);
	return 0;
}