#pragma GCC optimize(3)

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,m5=383008016,a=691504013,b=308495997,mod=1e9+9;

int fac[maxn],invf[maxn],A[maxn],B[maxn];

int Quick_Pow(int a,LL b) {
	int sum=1;
	for(; b; b>>=1,a=1ll*a*a%mod)if(b&1)sum=1ll*sum*a%mod;
	return sum;
}

int inv(int x) {return Quick_Pow(x,mod-2);}

int C(int a,int b) {return 1ll*fac[a]*invf[b]%mod*invf[a-b]%mod;}

int main() {
	fac[0]=invf[0]=1;
	for(int i=1; i<maxn; i++) {
		fac[i]=1ll*fac[i-1]*i%mod;
		invf[i]=inv(fac[i]);
	}
	A[0]=B[0]=1;
	int t;
	scanf("%d",&t);
	while(t--) {
		LL n,c;
		int k;
		scanf("%lld%lld%d",&n,&c,&k);
		int tmpa=Quick_Pow(a,c),tmpb=Quick_Pow(b,c);
		for(int i=1; i<=k; i++) {
			A[i]=1ll*A[i-1]*tmpa%mod;
			B[i]=1ll*B[i-1]*tmpb%mod;
		}
		int ans=0;
		for(int i=0; i<=k; i++) {
			int x=1ll*A[k-i]*B[i]%mod,tmp=0;
			if(x==1)tmp=n%mod;
			else tmp=1ll*x*(Quick_Pow(x,n)-1+mod)%mod*inv(x-1)%mod;
			tmp=1ll*tmp*C(k,i)%mod;
			if(i&1)ans=(ans-tmp+mod)%mod;
			else ans=(ans+tmp)%mod;
		}
		ans=1ll*ans*Quick_Pow(inv(m5),k)%mod;
		printf("%d\n",ans);
	}
	return 0;
}