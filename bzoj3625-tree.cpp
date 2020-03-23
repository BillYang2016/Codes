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
const LL mod=998244353,g=3,inv2=499122177;

void check(LL &x) {
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}

void add(LL &x,LL v) {
	x+=v;
	check(x);
}

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
		for(int i=1; i<n; i++) {
			omega[i]=omega[i-1]*x%mod;
			iomega[i]=inv(omega[i]);
		}
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=(1<<(k-j-1));
			rev[i]=t;
		}
	}
	
	void transform(LL* a,LL* omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(LL* p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL t=omega[n/len*i]*p[mid+i]%mod;
					p[mid+i]=p[i]-t,check(p[mid+i]);
					add(p[i],t);
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

void polynomial_inverse(const LL* a,const int n,LL* b) {
	if(n==1) {
		b[0]=inv(a[0]);
		return;
	}
	polynomial_inverse(a,n>>1,b);
	int p=n<<1;
	static LL x[maxn];
	copy(a,a+n,x),fill(x+n,x+p,0);
	ntt.init(p),ntt.dft(x),ntt.dft(b);
	for(int i=0; i<p; i++)b[i]=b[i]*((2-x[i]*b[i]%mod+mod)%mod)%mod;
	ntt.idft(b),fill(b+n,b+p,0);
}

void polynomial_sqrt(const LL* a,const int n,LL* b) {
	if(n==1) {
		b[0]=1;
		return;
	}
	polynomial_sqrt(a,n>>1,b);
	int p=n<<1;
	static LL inv_b[maxn],x[maxn];
	fill(inv_b,inv_b+p,0);
	polynomial_inverse(b,n,inv_b);
	copy(a,a+n,x),fill(x+n,x+p,0);
	ntt.init(p),ntt.dft(x),ntt.dft(b),ntt.dft(inv_b);
	for(int i=0; i<p; i++)b[i]=(x[i]*inv_b[i]%mod+b[i])%mod*inv2%mod;
	ntt.idft(b),fill(b+n,b+p,0);
}

int n,m;
LL C[maxn],sqrt_C[maxn],inv_sqrt_C[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		if(x<=m)C[x]++;
	}
	C[0]=1;
	for(int i=1; i<=m; i++)C[i]=(-4*C[i]%mod+mod)%mod;
	int p=1;
	while(p<(m+1))p<<=1;
	polynomial_sqrt(C,p,sqrt_C);
	fill(C+m+1,C+p,0);
	add(sqrt_C[0],1);
	polynomial_inverse(sqrt_C,p,inv_sqrt_C);
	for(int i=1; i<=m; i++)printf("%lld\n",2*inv_sqrt_C[i]%mod);
	return 0;
}