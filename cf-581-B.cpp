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

LL n,l,r;

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; a*=a,b>>=1)if(b&1)ans*=a;
	return ans;
}

int main() {
	n=Get_Int();
	l=Get_Int();
	r=Get_Int();
	printf("%I64d %I64d\n",Quick_Pow(2,l)-1+n-l,Quick_Pow(2,r)+(n-r)*Quick_Pow(2,r-1)-1);
	return 0;
}
