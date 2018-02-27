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

inline const int Get_Int() {
	int num=0,bj=1;
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

const int maxn=262144+5;
const LL mod=1004535809;
LL g=3;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {
	return Quick_Pow(x,mod-2);
}

vector<int> ppt;

void find_root(LL x) {
	LL tmp=x-1;
	for(int i=2; i<=sqrt(tmp); i++)
		if(tmp%i==0) {
			ppt.push_back(i);
			while(tmp%i==0)tmp/=i;
		}
	for(g=2; g<x; g++) {
		bool bj=1;
		for(int t:ppt)
			if(Quick_Pow(g,(x-1)/t)==1) {
				bj=0;
				break;
			}
		if(bj)return;
	}
}

struct NumberTheoreticTransform {
	int n;
	LL omega[maxn],iomega[maxn];
	
	void init(int n) {
		this->n=n;
		int x=Quick_Pow(g,(mod-1)/n);
		omega[0]=iomega[0]=1;
		for(int i=1; i<n; i++) {
			omega[i]=omega[i-1]*x%mod;
			iomega[i]=inv(omega[i]);
		}
	}
	
	void transform(LL* a,LL* omega) {
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=(1<<(k-j-1));
			if(i<t)swap(a[i],a[t]);
		}
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(LL* p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL t=omega[n/len*i]*p[mid+i]%mod;
					p[mid+i]=(p[i]-t+mod)%mod;
					p[i]=(p[i]+t)%mod;
				}
		}
	}

	void dft(LL* a) {
		transform(a,omega);
	}

	void idft(LL* a) {
		transform(a,iomega);
		LL x=inv(n);
		for(int i=0; i<n; i++)a[i]=a[i]*x%mod;
	}
} ntt;

void polynomial_inverse(const LL* a,const int n,LL* ans) {
	if(n==1) {
		ans[0]=inv(a[0]);
		return;
	}
	int mid=ceil(n/2.0);
	polynomial_inverse(a,mid,ans);
	int p=1;
	while(p<n<<1)p<<=1;
	static LL x[maxn];
	copy(a,a+n,x);
	fill(x+n,x+p,0);
	ntt.init(p);
	ntt.dft(x);
	fill(ans+mid,ans+p,0);
	ntt.dft(ans);
	for(int i=0; i<p; i++)ans[i]=ans[i]*((2-x[i]*ans[i]%mod+mod)%mod)%mod;
	ntt.idft(ans);
}

LL n,fac[maxn],invi[maxn],invf[maxn],g1[maxn],G[maxn],C[maxn],_G[maxn];

int main() {
	// find_root(mod);
	n=Get_Int();
	fac[0]=invf[0]=invi[1]=1;
	for(int i=1; i<=n; i++) {
		fac[i]=fac[i-1]*i%mod;
		if(i!=1)invi[i]=(mod-mod/i)*invi[mod%i]%mod;
		invf[i]=invf[i-1]*invi[i]%mod;
	}
	g1[0]=g1[1]=1;
	for(int i=2; i<=n; i++)g1[i]=Quick_Pow(2,(LL)i*(i-1)/2%(mod-1));
	for(int i=0; i<=n; i++)G[i]=g1[i]*invf[i]%mod;
	for(int i=1; i<=n; i++)C[i]=g1[i]*invf[i-1]%mod;
	polynomial_inverse(G,n+1,_G);
	int p=1;
	while(p<(n+1)<<1)p<<=1;
	fill(_G+n+1,_G+p,0);
	ntt.init(p);
	ntt.dft(_G);
	ntt.dft(C);
	for(int i=0; i<=p; i++)_G[i]=_G[i]*C[i]%mod;
	ntt.idft(_G);
	printf("%lld\n",_G[n]*fac[n-1]%mod);
	return 0;
} 
