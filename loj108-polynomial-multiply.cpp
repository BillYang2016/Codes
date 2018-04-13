#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define cp complex<double>

const int maxn=262144+5;
const double pi=acos(-1);

struct FastFourierTransform {
	int n;
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
			for(int j=0; j<k; j++)if(i>>j&1)t|=1<<(k-1-j);
			rev[i]=t;
		}
	}
	void transform(cp *a,cp *omega) {
		for(int i=0; i<n; i++)if(i<rev[i])swap(a[i],a[rev[i]]);
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(cp *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					cp t=omega[n/len*i]*p[mid+i];
					p[mid+i]=p[i]-t;
					p[i]+=t;
				}
		}
	}
	void dft(cp *a) {transform(a,omega);}
	void idft(cp *a) {
		transform(a,iomega);
		for(int i=0; i<n; i++)a[i]/=n;
	}
} fft;

int n,m;
cp a[maxn],b[maxn];

int main() {
	n=Get_Int()+1;
	m=Get_Int()+1;
	int t=1;
	while(t<(n+m))t<<=1;
	fft.init(t);
	for(int i=0; i<n; i++)a[i]=cp(Get_Int(),0);
	for(int i=0; i<m; i++)b[i]=cp(Get_Int(),0);
	fft.dft(a),fft.dft(b);
	for(int i=0; i<t; i++)a[i]*=b[i];
	fft.idft(a);
	for(int i=0; i<n+m-1; i++)printf("%d\n",(int)round(a[i].real()));
	return 0;
}