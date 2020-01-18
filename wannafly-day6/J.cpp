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

const int maxn=55,p=998244353;

LL n,k,f[maxn],C[maxn][maxn],fac[maxn];

int main() {
	C[0][0]=fac[0]=1;
	for(int i=1; i<=50; i++) {
		fac[i]=fac[i-1]*i%p;
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++)C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		k=Get_Int();
		fill(f,f+n+1,0);
		f[0]=1;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=i; j++)
				if(k%j==0)f[i]=(f[i]+C[i-1][j-1]*fac[j-1]%p*f[i-j]%p)%p;
		printf("%lld\n",f[n]);
	}
	return 0;
}