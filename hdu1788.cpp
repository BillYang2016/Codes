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

int n,a;

int main() {
	while(true) {
		n=Get_Int();
		a=Get_Int();
		if(n==0&&a==0)break;
		LL ans=1;
		for(int i=1; i<=n; i++) {
			LL x=Get_Int();
			ans=ans/__gcd(x,ans)*x;
		}
		printf("%lld\n",ans-a);
	}
	return 0;
}