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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=1000000;
const LL mod=1e9+7;

LL n,fac[maxn+5],inv[maxn+5],invf[maxn+5],a[maxn+5],tmp[maxn+5],last=0,sum=0,ans=0;

LL C(LL n,LL m) {
	if(!m)return 1;
	return fac[n]*invf[m]%mod*invf[n-m]%mod;
}

int main() {
	fac[0]=1;
	for(int i=1; i<=maxn; i++)fac[i]=fac[i-1]*i%mod;
	inv[1]=invf[1]=invf[0]=1;
	for(int i=2; i<=maxn; i++) {
		inv[i]=(mod-(mod/i))*inv[mod%i]%mod;
		invf[i]=invf[i-1]*inv[i]%mod;
	}
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	sort(a+1,a+n+1);
	for(int i=1; i<=n; i++) {
		while(a[i]==a[i+1])sum++,i++;
		sum++;
		if(i==n)break;
		ans=(ans+(sum-last)*a[i]%mod*C(n,last)%mod*fac[last]%mod*fac[n-last-1]%mod)%mod;
		last=sum;
	}
	printf("%I64d\n",ans);
	return 0;
}