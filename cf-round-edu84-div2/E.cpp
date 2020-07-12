#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const LL mod=998244353;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

void add(LL &x,LL v) {x=(x+v)%mod;}

int main() {
	LL n=Get_Int();
	for(int i=1; i<n; i++) {
		LL ans=0;
		add(ans,2*10*9*Quick_Pow(10,n-i-1)%mod);
		if(i<=n-2)add(ans,(n-i-1)*10*9*9%mod*Quick_Pow(10,n-i-2)%mod);
		printf("%lld ",ans);
	}
	puts("10");
	return 0;
}