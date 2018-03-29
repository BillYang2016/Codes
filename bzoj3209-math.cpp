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

const LL mod=10000007;

LL n,f[65][65][2];
int cnt=0,a[65];

LL Dp(int Now,int times,bool up) {
	if(times>Now)return 0;
	if(Now==0)return times==0;
	if(~f[Now][times][up])return f[Now][times][up];
	int lim=up?a[Now]:1;
	LL &sum=f[Now][times][up];
	sum=0;
	for(int i=0; i<=lim; i++)sum+=Dp(Now-1,times-i,up&&(i==lim));
	return sum;
}

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

LL Solve(LL x) {
	memset(f,-1,sizeof(f));
	int cnt=0;
	while(x) {
		a[++cnt]=x&1;
		x>>=1;
	}
	LL ans=1;
	for(int i=1; i<=cnt; i++)ans=ans*Quick_Pow(i,Dp(cnt,i,1))%mod;
	return ans;
}

int main() {
	n=Get_Int();
	printf("%lld\n",Solve(n));
	return 0;
}