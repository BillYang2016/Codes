#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=262144+5;
const LL mod=998244353,g=3;

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

LL inv(LL x) {return Quick_Pow(x,mod-2);}

struct NumberTheoreticTransform {
	int n,rev[maxn];
	LL omega[maxn],iomega[maxn];
	void init(int n) {
		this->n=n;
		LL x=Quick_Pow(g,(mod-1)/n),y=inv(x);
		omega[0]=iomega[0]=1;
		for(int i=1; i<n; i++) {
			omega[i]=omega[i-1]*x%mod;
			iomega[i]=iomega[i-1]*y%mod;
		}
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i>>j&1)t|=1<<(k-1-j);
			rev[i]=t;
		}
	}
	void transform(LL *a,LL *omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(LL *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL t=omega[n/len*i]*p[mid+i]%mod;
					p[mid+i]=(p[i]-t+mod)%mod;
					p[i]=(p[i]+t)%mod;
				}
		}
	}
	void dft(LL *a) {transform(a,omega);}
	void idft(LL *a) {
		transform(a,iomega);
		LL x=inv(n);
		for(int i=0; i<n; i++)a[i]=a[i]*x%mod;
	}
} ntt;

int n,m;
LL a[maxn],b[maxn];

int main() {
	n=Get_Int()+1;
	m=Get_Int()+1;
	int t=1;
	while(t<(n+m))t<<=1;
	ntt.init(t);
	for(int i=0; i<n; i++)a[i]=Get_Int();
	for(int i=0; i<m; i++)b[i]=Get_Int();
	ntt.dft(a),ntt.dft(b);
	for(int i=0; i<t; i++)a[i]=a[i]*b[i]%mod;
	ntt.idft(a);
	for(int i=0; i<n+m-1; i++)printf("%lld ",a[i]);
	return 0;
}