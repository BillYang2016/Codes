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

int main() {
	int t=Get_Int();
	while(t--) {
		LL x=Get_Int(),y=Get_Int(),a=Get_Int(),b=Get_Int();
		if(x*y<0||a*2<b)printf("%lld\n",a*(abs(x)+abs(y)));
		else printf("%lld\n",b*min(x,y)+a*abs(x-y));
	}
	return 0;
}