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

const int maxn=65536+5,maxk=17;
const LL mod=998244353,g=3;

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

void Multiply(LL* a1,const int n1,LL* a2,const int n2,LL* ans) {
	int n=1;
	while(n<n1+n2)n<<=1;
	ntt.init(n);
	ntt.dft(a1);
	ntt.dft(a2);
	for(int i=0; i<n; i++)a1[i]=a1[i]*a2[i]%mod;
	ntt.idft(a1);
	for(int i=0; i<n1+n2-1; i++)ans[i]=a1[i];
}

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

LL tmp[maxn];

void polynomial_lnp(LL *a,LL *ans,int n) {
	polynomial_inverse(a,n,tmp);
	for(int i=0; i<n; i++)ans[i]=a[i+1]*(i+1)%mod; //求导
	ans[n]=0;
	Multiply(ans,n,tmp,n,ans);
	fill(ans+n+1,ans+2*n-2,0);
	for(int i=n; i>=1; i--)ans[i]=ans[i-1]*inv(i)%mod; //积分
	ans[0]=0;
}

int main() {
	n=30000;
	ntt.init(n);
	S[0][0]=fac[0]=invf[0]=1;
	for(int i=1; i<maxk; i++) {
		fac[i]=fac[i-1]*i%mod;
		invf[i]=inv(fac[i]);
		for(int j=1; j<maxk; j++)S[i][j]=(S[i-1][j-1]+S[i-1][j]*j)%mod;
	}
	for(int i=0; i<=n; i++)G[i]=Quick_Pow(2,i*(i-1)>>1)*invf[i]%mod;
	polynomial_lnp(G,F,n+1);
	Mul[0][0]=1;
	for(int i=1; i<maxk; i++) {
		Multiply(F,n+1,Mul[i-1],n+1,Mul[i]);
		fill(Mul[i]+n+2,Mul[i]+2*n,0);
	}
	for(int i=maxk-1; i>=1; i--) {
		for(int j=1; j<i; j++)
			for(int k=0; k<=n; k++)Mul[i][k]=(Mul[i][k]+Mul[j][k]*S[i][j])%mod;
		Multiply(Mul[i],n+1,G,n+1,Mul[i]);
		fill(Mul[i]+n+2,Mul[i]+2*n,0);
	}
	int t=Get_Int();
	while(t--) {
		int n=Get_Int(),m=Get_Int();
		printf("%lld\n",Mul[m][n]*fac[n]%mod);
	}
	return 0;
} 
