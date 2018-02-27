#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
#include<map>
using namespace std;

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

void Exgcd(LL a,LL b,LL &gcd,LL &x,LL &y) {
	if(!b)gcd=a,x=1,y=0;
	else Exgcd(b,a%b,gcd,y,x),y-=x*(a/b);
}
 
LL inv(LL a,LL mod) {
	LL gcd,x,y;
	Exgcd(a,mod,gcd,x,y);
	return (x+mod)%mod;
}
 
LL Quick_Pow(LL a,LL b,LL mod) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

int cnt=0;
LL fac[25][10505];
map<LL,int> M;

LL Fac(LL n,LL p,LL num) {
	if(n==0)return 1;
	int id=M[num];
	if(fac[id][0]==-1) {
		fac[id][0]=fac[id][1]=1;
		for(LL i=2; i<=num; i++)
			if(i%p)fac[id][i]=fac[id][i-1]*i%num;
			else fac[id][i]=fac[id][i-1];
	}
	LL sum=Quick_Pow(fac[id][num],n/num,num)*fac[id][n%num];
	return sum*Fac(n/p,p,num)%num;
}
 
LL Cal(LL n,LL p) {
	LL sum=0;
	for(LL i=n; i; i/=p)sum+=i/p;
	return sum;
}
 
LL C(LL n,LL m,LL p,LL num) {
	if(n<m)return 0;
	if(!M[num])M[num]=++cnt;
	LL x=Fac(n,p,num),y=Fac(m,p,num),z=Fac(n-m,p,num);
	LL sum=Cal(n,p)-Cal(m,p)-Cal(n-m,p);
	return x*inv(y,num)%num*inv(z,num)%num*Quick_Pow(p,sum,num)%num;
}

vector<LL> A,B;

LL ExLucas(LL n,LL m,LL mod) {
	LL x=mod,ans=0;
	if(A.empty()) {
		for(LL i=2; i<=sqrt(mod); i++)
			if(x%i==0) {
				LL num=1;
				while(x%i==0)x/=i,num*=i;
				A.push_back(i);
				B.push_back(num);
				LL Mi=mod/num;
				ans=(ans+Mi*inv(Mi,num)%mod*C(n,m,i,num)%mod)%mod;
			}
		if(x>1) {
			A.push_back(x);
			B.push_back(x);
			ans=(ans+mod/x*inv(mod/x,x)%mod*C(n,m,x,x)%mod)%mod;
		}
	} else {
		for(int i=0; i<A.size(); i++) {
			LL x=A[i],num=B[i];
			LL Mi=mod/num;
			ans=(ans+Mi*inv(Mi,num)%mod*C(n,m,x,num)%mod)%mod;
		}
	}
	return ans;
}

LL n,m,n1,n2,p,a[25];

#define C(n,m) ExLucas(n,m,p)


int main() {
	memset(fac,-1,sizeof(fac));
	int t=Get_Int();
	p=Get_Int();
	while(t--) {
		n=Get_Int();
		n1=Get_Int();
		n2=Get_Int();
		m=Get_Int();
		for(int i=1; i<=n1+n2; i++)a[i]=Get_Int();
		for(int i=n1+1; i<=n1+n2; i++)m-=a[i]-1;
		LL ans=C(m-1,n-1);
		for(int S=1; S<(1<<n1); S++) {
			LL cnt=0,tmpm=m;
			for(int i=0; i<n1; i++)if(S&(1<<i))cnt++,tmpm-=a[i+1];
			cnt=(cnt&1)?-1:1;
			ans=(ans+cnt*C(tmpm-1,n-1)+p)%p;
		}
		printf("%lld\n",ans);
	}
	return 0;
} 