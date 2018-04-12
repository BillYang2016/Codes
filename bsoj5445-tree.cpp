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

const int maxn=105,mod=1004535809;

void add(LL &x,LL v) {x=x+v>=mod?x+v-mod:x+v;}

int n,a[maxn];
LL fac[maxn],inv[maxn],f[maxn][maxn][maxn];

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

int main() {
	n=Get_Int();
	fac[0]=1;
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		fac[i]=fac[i-1]*i%mod;
	}
	inv[n]=Quick_Pow(fac[n],mod-2);
	for(int i=n; i>=1; i--)inv[i-1]=inv[i]*i%mod;
	f[0][0][0]=1;
	for(int i=0; i<n; i++)
		for(int j=0; j<=i; j++)
			for(int k=0; k<=n; k++)if(f[i][j][k]) {
				add(f[i+1][j][k],f[i][j][k]);
				for(int t=0; t<=min(n-2-k,a[i+1]-1); t++)add(f[i+1][j+1][k+t],f[i][j][k]*inv[t]%mod);
			}
	printf("%d ",n);
	for(int i=2; i<=n; i++)printf("%lld ",f[n][i][i-2]*fac[i-2]%mod);
	return 0;
}