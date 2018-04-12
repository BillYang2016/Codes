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

LL Mul(LL a,LL b,LL p) {
	LL tmp=(a*b-(LL)((long double)a/p*b+1e-8)*p);
	return tmp<0?tmp+p:tmp;
}

LL Quick_Pow(LL a,LL b,LL p) {
	LL sum=1;
	for(a%=p; b; b>>=1,a=Mul(a,a,p))if(b&1)sum=Mul(sum,a,p);
	return sum;
}

mt19937 g(rand());

bool Witness(LL a,LL n) {
	LL u=n-1,t=0;
	while(u%2==0)t++,u>>=1;
	LL x=Quick_Pow(a,u,n);
	for(int i=1; i<=t&&x!=1; i++,x=Mul(x,x,n))if(x!=n-1&&Mul(x,x,n)==1)return true;
	return x!=1;
}

bool Miller_Rabin(LL n) {
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	for(int i=1; i<=times; i++)if(Witness(g()%(n-1)+1,n))return false;
	return true;
}

LL Pollard_Rho(LL n) {
	if(!(n&1))return 2;
	while(true) {
		LL a=g()%(n-1)+1,b=a,c=g()%(n-1)+1;
		if(c==2)c=3;
		while(true) {
			a=(Mul(a,a,n)+c)%n;
			b=(Mul(b,b,n)+c)%n;
			b=(Mul(b,b,n)+c)%n;
			if(a==b)break; //环
			LL d=__gcd(abs(b-a),n);
			if(d>1)return d;
		}
	}
}

LL Find_Fac(LL n) {
	if(Miller_Rabin(n))return n;
	LL p=Pollard_Rho(n);
	return min(Find_Fac(p),Find_Fac(n/p));
}

LL n;

int main() {
	srand(time(NULL));
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		LL ans=Find_Fac(n);
		if(ans==n)puts("Prime");
		else printf("%lld\n",ans);
	}
	return 0;
}