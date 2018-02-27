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

const int maxa=10000000,TIMES=20;
const LL p=1e9+7,p2=p*p;

int Prime[maxa+5],u[maxa+5],pcnt=0;
bool vst[maxa+5];

void check(LL &x,LL p=p2) {
	if(x>=p)x-=p;
	if(x<0)x+=p;
}

void add(LL &x,LL v,LL p=p2) {
	x+=v;
	check(x,p);
}

void Table(int n) {
	u[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			Prime[++pcnt]=i;
			u[i]=-1;
		}
		for(int j=1; j<=pcnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {
				u[i*Prime[j]]=0;
				break;
			}
			u[i*Prime[j]]=-u[i];
		}
	}
	for(int i=2; i<=n; i++)u[i]+=u[i-1];
}

LL Mul(LL a,LL b,LL p=p2) {
	LL tmp=(a*b-(LL)((long double)a/p*b+1e-8)*p);
	check(tmp,p);
	return tmp;
}

LL Quick_Pow(LL a,LL b,LL p=p2) {
	LL sum=1;
	for(a%=p; b; b>>=1,a=Mul(a,a,p))if(b&1)sum=Mul(sum,a,p);
	return sum;
}

void Exgcd(LL a,LL b,LL &gcd,LL &x,LL &y) {
	if(!b)gcd=a,x=1,y=0;
	else Exgcd(b,a%b,gcd,y,x),y-=x*(a/b);
}

LL inv(LL a,LL p=p2) {
	LL x,y,d;
	Exgcd(a,p,d,x,y);
	return (x%p+p)%p;
}

mt19937 g(rand());

bool Witness(LL a,LL n) {
	LL u=n-1,t=0;
	while(u%2==0)t++,u>>=1;
	LL x=Quick_Pow(a,u,n);
	if(x==1)return false;
	for(int i=1; i<=t; i++,x=Mul(x,x,n))
		if(x!=n-1&&x!=1&&Mul(x,x,n)==1)return true;
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
			a=(Mul(a,a,n)+c)%n;
			b=(Mul(b,b,n)+c)%n;
			b=(Mul(b,b,n)+c)%n;
			if(a==b)break;
			LL d=__gcd(abs(b-a),n);
			if(d>1)return d;
		}
	}
}

vector<LL> vec;

void Find_Fac(LL n) {
	if(Miller_Rabin(n)) {
		vec.push_back(n);
		return;
	}
	LL p=Pollar_Rho(n);
	Find_Fac(p);
	Find_Fac(n/p);
}

LL n,m,a,ans;
int cnt[105];

LL f(LL n) {
	return (Quick_Pow(m-1,n)+(m-1)*(n&1?-1:1))%p2;
}

void Dfs(int Depth,LL sum,LL phi) {
	if(Depth==vec.size()) {
		add(ans,Mul(phi%p2,f(n/sum)));
		return;
	}
	LL tmp=1;
	for(int i=1; i<=cnt[Depth]; i++,tmp*=vec[Depth])Dfs(Depth+1,sum*tmp*vec[Depth],phi*tmp*(vec[Depth]-1));
	Dfs(Depth+1,sum,phi);
}

int main() {
	int t=Get_Int();
	Table(maxa);
	while(t--) {
		n=Get_Int();
		a=Get_Int();
		LL ans2=0,ans3=0;
		for(int i=1,next=0; i<=a; i=next+1) {
			next=a/(a/i);
			add(ans2,Mul(Mul(a/i,a/i),(u[next]-u[i-1])));
			add(ans3,Mul(Mul(Mul(a/i,a/i),a/i),(u[next]-u[i-1])));
		}
		m=Mul((ans3+ans2*3%p2+2)%p2,inv(6));
		vec.clear();
		Find_Fac(n);
		LL tmp=n;
		for(int i=0; i<vec.size(); i++) {
			cnt[i]=0;
			while(tmp%vec[i]==0) {
				tmp/=vec[i];
				cnt[i]++;
			}
		}
		ans=0;
		Dfs(0,1,1);
		if(n%p==0)printf("%lld\n",Mul(ans/p,inv(n/p,p),p));
		else printf("%lld\n",Mul(ans,inv(n,p),p));
	}
	return 0;
}