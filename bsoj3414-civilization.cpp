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

const int maxn=205;
const LL mod1=1e9+7,mod2=1e9+9,mod=mod1*mod2;

int n;
LL a[maxn][maxn],b[maxn][maxn],Ans[maxn];
char s[maxn][1005];

LL Mul(LL a,LL b) {
	LL ans=0;
	for(; b; b>>=1,a=(a+a)%mod)if(b&1)ans=(ans+a)%mod;
	return ans;
}

void Exgcd(LL a,LL b,LL &gcd,LL &x,LL &y) {
	if(!b)gcd=a,x=1,y=0;
	else Exgcd(b,a%b,gcd,y,x),y-=x*(a/b);
}

LL inv(LL a,LL p) {
	LL d,x,y;
	Exgcd(a,p,d,x,y);
	return (x%p+p)%p;
}

void Gauss_Jordan(int n,LL mod,LL a[][maxn]) {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++)a[i][j]%=mod;
		int len=strlen(s[i]);
		for(int j=0; j<len; j++)a[i][n+1]=(a[i][n+1]*10+s[i][j]-'0')%mod;
	}
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(a[row][i])break;
		if(row>n)continue;
		for(int j=1; j<=n+1; j++)swap(a[i][j],a[row][j]);
		LL t=inv(a[i][i],mod);
		for(int j=1; j<=n+1; j++)a[i][j]=a[i][j]*t%mod;
		for(int j=1; j<=n; j++)
			if(j!=i) {
				t=a[j][i];
				for(int k=1; k<=n+1; k++)a[j][k]=(a[j][k]+mod-t*a[i][k]%mod)%mod;
			}
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++)a[i][j]=b[i][j]=Get_Int();
		scanf("%s",s[i]);
	}
	Gauss_Jordan(n,mod1,a);
	Gauss_Jordan(n,mod2,b);
	LL inv1=inv(mod2,mod1),inv2=inv(mod1,mod2);
	for(int i=1; i<=n; i++) {
		LL a1=a[i][n+1],a2=b[i][n+1];
		printf("%lld\n",(Mul(mod2*inv1%mod,a1)+Mul(mod1*inv2%mod,a2))%mod);
	}
	return 0;
}