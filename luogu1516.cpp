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

LL x,y,m,n,L;

int main() {
	x=Get_Int();
	y=Get_Int();
	m=Get_Int();
	n=Get_Int();
	L=Get_Int();
	LL x0,y0,a=m-n,c=y-x;
	if(a<0)a*=-1,c*=-1;
	LL d=Exgcd(a,L,x0,y0);
	if(c%d)puts("Impossible");
	else {
		x0=x0*c/d;
		LL t=(x0%(L/d)+(L/d))%(L/d);
		printf("%lld\n",t);
	}
	return 0;
}