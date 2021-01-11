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

LL a1,r1,a2,r2,a[15],r[15];

LL ExCRT() {
	a1=a[1];
	r1=r[1];
	bool flag=1;
	for(int i=2; i<=n; i++) {
		a2=a[i];
		r2=r[i];
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
	int t=Get_Int();
	while(t--) {
		LL range=Get_Int();
		n=Get_Int();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		for(int i=1; i<=n; i++)r[i]=Get_Int();
		LL ans=ExCRT();
		if(ans==-1||ans>range)puts("0");
		else printf("%lld\n",(range-ans)/a1+1-(ans==0));
	}
	return 0;
}