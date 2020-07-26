#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=1000005;
const LL mod=998244353;

LL fac[maxn],invf[maxn];

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(int x) {return Quick_Pow(x,mod-2);}

LL C(int n,int m) {return fac[n]*invf[m]%mod*invf[n-m]%mod;}

int main() {
	fac[0]=1;
	for(int i=1; i<maxn; i++)fac[i]=fac[i-1]*i%mod;
	invf[maxn-1]=inv(fac[maxn-1]);
	for(int i=maxn-2; i>=0; i--)invf[i]=invf[i+1]*(i+1)%mod;
	int t=Get_Int();
	while(t--) {
		int n=Get_Int(),m=Get_Int(),k=Get_Int();
		LL ans=0;
		for(int i=k; i<=min(n,m); i++)ans=(ans+C(i-1,k-1)*C(n-i+k-1,k-1)%mod*C(m-i+k-1,k-1)%mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}