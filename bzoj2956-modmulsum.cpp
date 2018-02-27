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

const LL mod=19940417;

LL n,m,ans1=0,ans2=0,ans,sum=0,tmp=0;

LL Cal1(LL x,LL y) {
	return (y+x)*(y-x+1)/2%mod;
}

LL Cal2(LL x,LL y) {
	return (((__int128)y*(y+1)*(2*y+1)/6%mod-(__int128)(x-1)*x*(2*x-1)/6%mod)%mod+mod)%mod;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	if(n>m)swap(n,m);
	LL next;
	for(LL i=1; i<=n; i=next+1) {
		next=n/(n/i);
		ans1=(ans1+(n/i)*Cal1(i,next)%mod)%mod;
	}
	for(LL i=1; i<=m; i=next+1) {
		next=m/(m/i);
		ans2=(ans2+(m/i)*Cal1(i,next)%mod)%mod;
	}
	ans=(((n*n%mod*m%mod*m%mod)+ans1*ans2%mod-ans1*m%mod*m%mod-ans2*n%mod*n%mod)%mod+mod)%mod;
	for(LL i=1; i<=min(n,m); i=next+1) {
		next=min(m/(m/i),n/(n/i));
		tmp=(tmp+(n/i)*(m/i)%mod*Cal2(i,next)%mod)%mod;
	}
	for(LL i=1; i<=n; i=next+1) {
		next=min(m/(m/i),n);
		sum=(sum+(m/i)*Cal1(i,next)%mod)%mod;
	}
	sum=((n*n%mod*m%mod+tmp-ans1*m%mod-sum*n%mod)%mod+mod)%mod;
	printf("%lld\n",((ans-sum)%mod+mod)%mod);
	return 0;
} 