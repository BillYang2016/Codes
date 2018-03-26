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

const int maxn=55;

int n,a[maxn],G[maxn][maxn];
LL m,p,Pow[maxn*maxn+maxn],fac[maxn],inv[maxn],invf[maxn],ans=0;

int gcd(int a,int b) {return b==0?a:(G[a][b]?G[a][b]:G[a][b]=gcd(b,a%b));}

void Dfs(int dep,int sum,int last) {
	if(!sum) {
		LL s=fac[n],c=0,len=0;
		for(int i=1; i<=dep; i++) {
			len++;
			if(i==dep||a[i]!=a[i+1])s=s*invf[len]%p,len=0;
			s=s*inv[a[i]]%p;
			c+=a[i]>>1;
			for(int j=1; j<i; j++)c+=gcd(a[i],a[j]);
		}
		ans=(ans+Pow[c]*s)%p;
		return;
	}
	for(int i=min(sum,last); i>=1; i--)a[dep+1]=i,Dfs(dep+1,sum-i,i);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	p=Get_Int();
	Pow[0]=1;
	for(int i=1; i<=n*n+n; i++)Pow[i]=Pow[i-1]*m%p;
	fac[1]=inv[1]=invf[1]=fac[0]=inv[0]=invf[0]=1;
	for(int i=2; i<=n; i++) {
		fac[i]=fac[i-1]*i%p;
		inv[i]=p-(p/i)*inv[p%i]%p;
		invf[i]=invf[i-1]*inv[i]%p;
	}
	Dfs(0,n,n);
	printf("%lld\n",ans*invf[n]%p);
	return 0;
}