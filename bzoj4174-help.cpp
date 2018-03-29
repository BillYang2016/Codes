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

int vst[maxn],u[maxn],p[maxn],cnt=0;

void Mobius_Table(int n) {
	u[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {p[++cnt]=i;u[i]=-1;}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {u[i*Prime[j]]=0;break;}
			u[i*Prime[j]]=-u[i];
		}
	}
}

LL f(LL n) {return (n*(n+1)>>1)%mod;}

int main() {
	n=Get_Int();
	m=Get_Int();
	if(n>m)swap(n,m);
	Mobius_Sieve(n);
	ans=(f(n)*f(m)%mod-f(n)*m%mod-f(m)*n%mod+2*mod)%mod;
	for(int i=1; i<=n; i++)
		for(int j=1; i*j<=n; j++)ans=(ans+(i+x/i*i*2)*u[j]%mod*(n/i/j)%mod*(m/i/j)%mod)%mod;
	printf("%lld\n",ans*(m+1>>1)%mod);
	return 0;
}