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

const int maxn=25,maxs=1<<20;
const int p=998244353,inv4=748683265;

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans;
}

LL a[maxn];
int n,m,f[maxn],cnt[maxs],g[maxs],ans=0;

void add(int &x,int v) {x=x+v>=p?x+v-p:x+v;}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++)a[i]=Get_Int();
	LL w0=1,w1=Quick_Pow(3,(p-1)/4),w2=w1*w1%p,w3=w2*w1%p;
	for(int i=0; i<=m; i++)f[i]=(i&1?-1:1)*inv4*(Quick_Pow(1-w0,i)+Quick_Pow(1-w1,i)+Quick_Pow(1-w2,i)+Quick_Pow(1-w3,i))%p;
	for(int S=1; S<(1<<m); S++)cnt[S]=cnt[S-(S&-S)]+1;
	for(int S=0; S<(1<<m); S++) {
		LL lcm=1;
		for(int i=1; i<=m; i++)if(S>>(i-1)&1) {
			lcm=lcm*a[i]/__gcd(lcm,a[i]);
			if(lcm>n)break;
		}
		g[S]=(n/lcm)*f[cnt[S]]%p;
	}
	for(int i=0; i<m; i++)
		for(int S=0; S<(1<<m); S++)if(S>>i&1)add(g[S],g[S^(1<<i)]);
	for(int S=0; S<(1<<m); S++)add(ans,g[S]);
	printf("%lld\n",(ans*Quick_Pow(1<<m,p-2)%p+p)%p);
	return 0;
}