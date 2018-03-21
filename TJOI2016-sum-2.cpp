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

const int maxn=262144+5;
const LL mod=998244353,g=3;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {return Quick_Pow(x,mod-2);}

struct NumberTheoreticTransform {
	int n,rev[maxn];
	LL omega[maxn],iomega[maxn];
	void init(int n) {
		this->n=n;
		int x=Quick_Pow(g,(mod-1)/n);
		omega[0]=iomega[0]=1;
		for(int i=1; i<n; i++)omega[i]=omega[i-1]*x%mod,iomega[i]=inv(omega[i]);
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=1<<(k-j-1);
			rev[i]=t;
		}
	}
	void transform(LL *a,LL *omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2; len<=n; len*=2) {
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

int n;
LL a[maxn],b[maxn],fac[maxn],invf[maxn];

int main() {
	n=Get_Int();
	int T=1;
	while(T<=n)T<<=1;
	fac[0]=1;
	for(int i=1; i<=T; i++)fac[i]=fac[i-1]*i%mod;
	invf[T]=inv(fac[T]);
	for(int i=T; i>=1; i--)invf[i-1]=invf[i]*i%mod;
	a[0]=b[0]=1,b[1]=n+1;
	for(int i=1; i<=n; i++) {
		a[i]=((i&1?-1:1)*invf[i]+mod)%mod;
		if(i>1)b[i]=inv(i-1)*(Quick_Pow(i,n+1)-1)%mod*invf[i]%mod;
	}
	T<<=1;
	ntt.init(T);
	ntt.dft(a),ntt.dft(b);
	for(int i=0; i<T; i++)a[i]=a[i]*b[i]%mod;
	ntt.idft(a);
	LL ans=0;
	for(int i=0; i<=n; i++)ans=(ans+Quick_Pow(2,i)*fac[i]%mod*a[i]%mod)%mod;
	printf("%lld\n",ans);
	return 0;
}