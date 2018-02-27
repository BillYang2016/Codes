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

#define cp complex<double>

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
		for(int i=1; i<=n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=1<<(k-j-1);
			rev[i]=t;
		}
	}
	void transform(cp* a,cp* omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(cp p=a; p!=a+n; p+=len) {
				for(int i=0; i<mid; i++) {
					cp t=omega[n/len*i]*p[mid+i];
					p[mid+i]=p[i]-t;
					p[i]+=t;
				}
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

void Multiply(const int* a1,const int n1,const int* a2,const int n2,int* ans) {
	int n=1;
	while(n<n1+n2)n<<=1;
	static cp c1[maxn],c2[maxn];
	for(int i=0; i<n1; i++)c1[i].real(a1[i]);
	for(int i=0; i<n2; i++)c2[i].real(a2[i]);
	fft.init(n);
	fft.dft(c1);
	fft.dft(c2);
	for(int i=0; i<n; i++)c1[i]*=c2[i];
	fft.idft(c1);
	for(int i=0; i<n1+n2-1; i++)ans[i]=round(c1[i].real());
}

int main() {
	t=Get_Int();
	while(t--) {
		Clear();
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			int x=Get_Int();
			Hash[x]++;
			a[x]++;
			Max=max(Max,x);
		}
		for(int i=Max; i>=1; i--)sum[i]=sum[i+1]+Hash[i];
		Multiply(a,Max,a,Max,b);
		for(int i=0; i<=n; i++) {
			if(!(i&1))b[i]-=Hash[i>>1];
			b[i]>>=1;
		}
		double up=down=(double)n*(n-1)*(n-2)/6;
		for(int i=0; i<=n; i++)up-=b[i]*sum[i];
		printf("%0.7lf\n",up/down);
	}
	return 0;
}