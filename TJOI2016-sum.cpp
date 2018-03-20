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

void polynomial_inverse(const LL* a,const int n,LL* b) {
	if(n==1) {b[0]=inv(a[0]);return;}
	polynomial_inverse(a,n>>1,b);
	int p=n<<1;
	static LL x[maxn];
	copy(a,a+n,x),fill(x+n,x+p,0);
	ntt.init(p),ntt.dft(x),ntt.dft(b);
	for(int i=0; i<p; i++)b[i]=b[i]*((2-x[i]*b[i]%mod+mod)%mod)%mod;
	ntt.idft(b),fill(b+n,b+p,0);
}

int n;
LL fac[maxn],invf[maxn],F[maxn],G[maxn];

int main() {
	n=Get_Int();
	int T=1;
	while(T<=n)T<<=1;
	fac[0]=1;
	for(int i=1; i<=T; i++)fac[i]=fac[i-1]*i%mod;
	invf[T]=inv(fac[T]);
	for(int i=T; i>=1; i--)invf[i-1]=invf[i]*i%mod;
	for(int i=1; i<=n; i++)F[i]=(mod-invf[i])*2%mod;
	F[0]=1;
	polynomial_inverse(F,T,G);
	LL ans=0;
	for(int i=n; i>=0; i--)ans=(ans+G[i]*fac[i]%mod)%mod;
	printf("%lld\n",ans);
	return 0;
}