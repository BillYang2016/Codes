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

const int maxn=131072+5;
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

LL inv(LL x) {
	return Quick_Pow(x,mod-2);
}

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
	copy(a,a+n,x),fill(x+n,x+p,0);
	ntt.init(p);
	ntt.dft(x);
	fill(ans+mid,ans+p,0);
	ntt.dft(ans);
	for(int i=0; i<p; i++)ans[i]=ans[i]*((2-x[i]*ans[i]%mod+mod)%mod)%mod;
	ntt.idft(ans);
}

void polynomial_sqrt(const LL* a,const int n,LL* ans) {
	if(n==1) {
		ans[0]=1;
		return;
	}
	int mid=ceil(n/2.0);
	polynomial_sqrt(a,mid,ans);
	int p=1;
	while(p<n<<1)p<<=1;
	static LL inv_b[maxn];
	fill(inv_b,inv_b+n,0);
	polynomial_inverse(ans,n,inv_b);
	fill(inv_b+n,inv_b+p,0);
	static LL x[maxn];
	copy(a,a+n,x),fill(x+n,x+p,0);
	ntt.init(p);
	ntt.dft(x);
	fill(ans+mid,ans+p,0);
	ntt.dft(ans);
	ntt.dft(inv_b);
	for(int i=0; i<p; i++)ans[i]=inv2*(x[i]*inv_b[i]%mod+ans[i])%mod;
	ntt.idft(ans);
}

void Multiply(const LL* a1,const int n1,const LL* a2,const int n2,LL* ans) {
	int n=1;
	while(n<n1+n2)n<<=1;
	static LL c1[maxn],c2[maxn];
	copy(a1,a1+n1,c1),fill(c1+n1,c1+n,0);
	copy(a2,a2+n1,c2),fill(c2+n1,c2+n,0);
	ntt.init(n);
	ntt.dft(c1);
	ntt.dft(c2);
	for(int i=0; i<n; i++)c1[i]=c1[i]*c2[i]%mod;
	ntt.idft(c1);
	for(int i=0; i<n1+n2-1; i++)ans[i]=c1[i];
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		if(x<=m)C[x]++;
	}
	C[0]=1;
	for(int i=1; i<=m; i++)C[i]=(-4*C[i]%mod+mod)%mod;
	polynomial_sqrt(c,m+1,sqrt_c);
	int p=1;
	while(p<((m+1)<<1))p<<=1;
	fill(C+m+1,C+p,0);
	add(sqrt_c[0],1);
	polynomial_inverse(root_c,m+1,inv_root_c);
	fill(inv_root_c+m+1,inv_root_c+n,0);
	for(int i=1; i<=m; i++)printf("%lld\n",2*inv_root_c[i]%mod);
	return 0;
} 
