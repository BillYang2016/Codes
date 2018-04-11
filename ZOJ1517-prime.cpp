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

const int times=10;

mt19937 g(rand());

LL Quick_Pow(LL a,LL b,LL p) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans;
}

bool Witness(LL a,LL n) {
	LL u=n-1,t=0;
	while(!(u&1))u>>=1,t++;
	LL x=Quick_Pow(a,u,n);
	for(int i=1; i<=t; i++,x=x*x%n)
		if(x==1)return 0;
		else if(x!=n-1&&x*x%n==1)return 1;
	return x!=1;
}

bool Miller_Rabin(LL n) {
	if(n==2)return 1;
	if(n<2||!(n&1))return 0;
	srand(time(NULL));
	for(int i=1; i<=times; i++)if(Witness(g()%(n-1)+1,n))return 0;
	return 1;
}

LL n;

int main() {
	while(~scanf("%lld",&n))puts(Miller_Rabin(n)?"Yes":"No");
	return 0;
}