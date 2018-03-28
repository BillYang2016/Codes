#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int TIMES=10;

LL Quick_Mul(LL a,LL b,LL p) {
	LL tmp=(a*b-(LL)((long double)a/p*b+1e-8)*p);
	if(tmp<0)return tmp+p;
	else return tmp;
}

LL Quick_Pow(LL a,LL b,LL p) {
	LL sum=1;
	for(a%=p; b; b>>=1,a=Quick_Mul(a,a,p))if(b&1)sum=Quick_Mul(sum,a,p);
	return sum;
}

mt19937 g(rand());

bool Witness(LL a,LL n) {
	LL u=n-1,t=0;
	while(u%2==0)t++,u>>=1;
	LL x=Quick_Pow(a,u,n);
	if(x==1)return false;
	for(int i=1; i<=t; i++,x=Quick_Mul(x,x,n))
		if(x!=n-1&&x!=1&&Quick_Mul(x,x,n)==1)return true;
	return x!=1;
}

bool Miller_Rabin(LL n) {
	if(n==2)return true;
	if(n<2||!(n&1))return false;
	for(int i=1; i<=TIMES; i++)
		if(Witness(g()%(n-1)+1,n))return false;
	return true;
}

LL Pollar_Rho(LL n) {
	if(!(n&1))return 2;
	while(true) {
		LL a=g()%(n-1)+1,b=a,c=g()%(n-1)+1;
		if(c==2)c=3;
		while(true) {
			a=(Quick_Mul(a,a,n)+c)%n;
			b=(Quick_Mul(b,b,n)+c)%n;
			b=(Quick_Mul(b,b,n)+c)%n;
			if(a==b)break;
			LL d=__gcd(abs(b-a),n);
			if(d>1)return d;
		}
	}
}

vector<int> fac;

void Find_Fac(LL n) {
	if(Miller_Rabin(n)) {fac.push_back(n);return;}
	LL p=Pollar_Rho(n);
	Find_Fac(p);
	Find_Fac(n/p);
}

LL gcd,lcm;

int main() {
	while(~scanf("%lld%lld",&gcd,&lcm)) {
		if(gcd==lcm) {printf("%lld %lld\n",gcd,lcm);continue;}
		LL n=lcm/gcd;
		fac.clear();
		Find_Fac(n);
		sort(fac.begin(),fac.end());
		fac.erase(unique(fac.begin(),fac.end()),fac.end());
		int all=1<<(fac.size());
		LL ans=LLONG_MAX/2,ansa=0,ansb=0;
		for(int S=0; S<all; S++) {
			LL a=1;
			for(int i=0; i<fac.size(); i++)if(S&(1<<i)) {
				LL tmp=n,sum=1;
				while(tmp%fac[i]==0)tmp/=fac[i],sum*=fac[i];
				a*=sum;
			}
			LL b=n/a;
			if((a+b)*gcd<ans) {
				ans=(a+b)*gcd;
				ansa=min(gcd*a,gcd*b);
				ansb=max(gcd*a,gcd*b);
			}
		}
		printf("%lld %lld\n",ansa,ansb);
	}
	return 0;
}