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

bool Miller_Rabin(LL x) {
	if(x==2)return 1;
	if(x<2||!(x&1))return 0;
	srand(time(NULL));
	for(int i=1; i<=times; i++)if(Quick_Pow(g()%(x-1)+1,x-1,x)!=1)return 0;
	return 1;
}

LL n;

int main() {
	while(~scanf("%lld",&n))puts(Miller_Rabin(n)?"Yes":"No");
	return 0;
}