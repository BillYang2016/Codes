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

const int maxn=1000000;
const LL mod=1e9+7;

LL fac[maxn+5],f[maxn+5],inv[maxn+5];

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL C(LL n,LL m) {
	return fac[n]*inv(m)%mod*inv(n-m)%mod;
}

int main() {
	fac[0]=f[0]=1;
	for(int i=1; i<=maxn; i++) {
		fac[i]=fac[i-1]*i%mod;
		inv[i]=Quick_Pow(fac[i],mod-2);
		f[i]=(i-1)*(f[i-1]+f[i-2])%mod;
	}
	t=Get_Int();
	while(t--) {
		int n=Get_Int(),m=Get_Int();
		printf("%lld\n",C(n,m)*f[n-m]%mod);
	}
	return 0;
} 
