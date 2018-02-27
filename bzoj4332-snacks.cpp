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

const int maxn=32768+5;
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

int n,m,N,p,o,s,u,h[maxn];
cp f[maxn],tmp[maxn],g[maxn];

void Solve(cp *g,int *h,int n) {
	if(n==0) {
		g[0]=1;
		return;
	}
	if(n&1) {
		Solve(g,h,n-1);
		fft.dft(g);
		for(int i=0; i<N; i++)g[i]*=f[i];
		fft.idft(g);
		for(int i=0; i<=m; i++)g[i]=cp((int)round(g[i].real())%p,0),h[i]=(h[i]+(int)g[i].real())%p;
		for(int i=m+1; i<N; i++)g[i]=0;
	} else {
		Solve(g,h,n>>1);
		for(int i=0; i<N; i++)tmp[i]=cp(h[i],0);
		fft.dft(g),fft.dft(tmp);
		for(int i=0; i<N; i++)tmp[i]*=g[i],g[i]*=g[i];
		fft.idft(g),fft.idft(tmp);
		for(int i=0; i<=m; i++)g[i]=cp((int)round(g[i].real())%p,0),h[i]=(h[i]+(int)round(tmp[i].real()))%p;
		for(int i=m+1; i<N; i++)g[i]=0;
	}
}

int main() {
	m=Get_Int();
	p=Get_Int();
	n=Get_Int();
	o=Get_Int();
	s=Get_Int();
	u=Get_Int();
	N=1;
	while(N<((m+1)<<1))N<<=1;
	fft.init(N);
	for(int i=1; i<=m; i++)f[i].real((o*i*i+s*i+u)%p);
	fft.dft(f);
	Solve(g,h,n);
	printf("%d\n",h[m]);
	return 0;
}
