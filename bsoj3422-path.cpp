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

const LL mod=1e9+7;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {
	return Quick_Pow(x,mod-2);
}

LL n,m;

int main() {
	n=Get_Int()+1;
	m=Get_Int()+1;
	LL C=1,Min=min(n,m),Max=max(n,m),down=1,up=1;
	for(LL i=1; i<Min; i++)down=down*i%mod;
	for(LL i=Max+1; i<Max+Min; i++)up=up*i%mod;
	printf("%lld\n",(up*inv(down)%mod+Max-1)%mod);
	return 0;
} 
