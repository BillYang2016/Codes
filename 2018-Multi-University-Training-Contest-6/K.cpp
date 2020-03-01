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

const int maxn=100005,maxp=1299709+5;
const int maxf=maxn+maxp;
const LL mod=1e9+7;

int cnt=0,Prime[maxn];
bool vst[maxp];
LL fac[maxf],invf[maxf];

void Prime_Sieve() {
	for(int i=2; cnt<maxn; i++) {
		if(!vst[i])Prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*Prime[j]<=maxp; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
}

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {return Quick_Pow(x,mod-2);}

LL C(LL n,LL m) {return fac[n]*invf[m]%mod*invf[n-m]%mod;}

LL Cal(LL x,LL n) { //n阶等比数列求和
	if(x==1)return n;
	return (Quick_Pow(x,n)-1+mod)%mod*x%mod*inv(x-1)%mod;
}

int main() {
	fac[0]=1;
	for(int i=1; i<maxf; i++)fac[i]=fac[i-1]*i%mod;
	invf[maxf-1]=inv(fac[maxf-1]);
	for(int i=maxf-2; i>=0; i--)invf[i]=invf[i+1]*(i+1)%mod;
	Prime_Sieve();
	int t=Get_Int();
	while(t--) {
		LL p=Prime[Get_Int()],n=Get_Int(),k=Get_Int(),ans=0;
		for(int j=1; j<=k; j++)ans=(ans+Cal(C(p+j,p-1),n))%mod;
		printf("%lld\n",ans);
	}
	return 0;
}