#include<algorithm>
#include<iostream>
#include<cstring>
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

LL d;

LL CRT(LL n,LL* a,LL* b) {
	LL M=1,ans=0;
	for(int i=1; i<=n; i++)M*=b[i];
	for(int i=1; i<=n; i++) {
		LL Mi=M/b[i],x0,y0;
		Exgcd(Mi,b[i],x0,y0);
		ans=(ans+Mi*x0*a[i])%M;
	}
	ans=(((ans+M)%M-d)%M+M)%M;
	if(ans==0)ans=M;
	return ans;
}

LL a[5],r[5];

int main() {
	for(int i=1; ; i++) {
		a[1]=23;
		a[2]=28;
		a[3]=33;
		r[1]=Get_Int()%a[1];
		r[2]=Get_Int()%a[2];
		r[3]=Get_Int()%a[3];
		d=Get_Int();
		if(d==-1)break;
		printf("Case %d: the next triple peak occurs in %lld days.\n",i,CRT(3,r,a));
	}
	return 0;
}