#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>

using namespace std;

typedef long long LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n;

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

LL a1,r1,a2,r2;

LL ExCRT() {
	a1=Get_Int();
	r1=Get_Int();
	bool flag=1;
	for(int i=2; i<=n; i++) {
		a2=Get_Int();
		r2=Get_Int();
		LL a=a1,b=a2,c=r2-r1,x0,y0;
		LL gcd=Exgcd(a,b,x0,y0);
		if(c%gcd!=0)flag=0;
		x0=(x0*(c/gcd)%(b/gcd)+b/gcd)%(b/gcd);
		r1=a1*x0+r1;
		a1=a1/gcd*a2;
	}
	if(!flag)return -1;
	return r1;
}

int main() {
	while(~scanf("%d",&n))printf("%lld\n",ExCRT());
	return 0;
}