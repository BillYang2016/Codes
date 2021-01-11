#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>

using namespace std;

typedef unsigned long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

LL Exgcd(LL a,LL b,LL& x,LL& y) {
	if(b==0) {
		x=1;
		y=0;
		return a;
	}
	LL ans=Exgcd(b,a%b,x,y),tmp=x;
	x=y;
	y=tmp-a/b*y;
	return ans;
}

int main() {
	while(true) {
		LL a=Get_Int(),b=Get_Int(),c=Get_Int(),k=Get_Int();
		if(a+b+c+k==0)break;
		k=1ll<<k;
		LL x,y;
		LL d=Exgcd(c,k,x,y);
		if((b-a)%d) {puts("FOREVER");continue;}
		x=x*(b-a)/d;
		x=(x%(k/d)+(k/d))%(k/d);
		printf("%lld\n",x);
	}
	return 0;
}