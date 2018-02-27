#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<complex>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

#define cp complex<double>
typedef long long LL;

const int maxn=262144+5;
const double pi=acos(-1);

struct FastFourierTransform {
	int n,rev[maxn];
	cp omega[maxn],iomega[maxn];
	void init(int n) {
		this->n=n;
		for(int i=0; i<n; i++) {
			omega[i]=cp(cos(2*pi/n*i),sin(2*pi/n*i));
			iomega[i]=conj(omega[i]);
		}
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=1<<(k-j-1);
			rev[i]=t;
		}
	}
	void transform(cp* a,cp* omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(cp* p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					cp t=omega[n/len*i]*p[mid+i];
					p[mid+i]=p[i]-t;
					p[i]+=t;
				}
		}
	}
	void dft(cp* a) {
		transform(a,omega);
	}
	void idft(cp* a) {
		transform(a,iomega);
		for(int i=0; i<n; i++)a[i]/=n;
	}
} fft;

int n,m;
LL sum=0,sqr=0;
cp a[maxn],b[maxn],ans[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=0; i<n; i++) {
		int x=Get_Int();
		a[n-1-i].real(x);
		sum+=x,sqr+=x*x;
	}
	for(int i=0; i<n; i++) {
		int x=Get_Int();
		b[i].real(x),b[n+i]=b[i];
		sum-=x,sqr+=x*x;
	}
	int N=1;
	while(N<(n<<2))N<<=1;
	fft.init(N);
	fft.dft(a),fft.dft(b);
	for(int i=0; i<N; i++)ans[i]=a[i]*b[i];
	fft.idft(ans);
	LL Ans=LLONG_MAX;
	for(int k=0; k<n; k++)
		for(int c=0; c<=m; c++) {
			Ans=min(Ans,sqr+c*sum*2+n*c*c-2*(LL)round(ans[n-1+k].real()));
			Ans=min(Ans,sqr-c*sum*2+n*c*c-2*(LL)round(ans[n-1+k].real()));
		}
	printf("%lld\n",Ans);
	return 0;
}