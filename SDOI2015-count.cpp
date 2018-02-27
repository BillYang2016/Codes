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

const int maxn=32768+5;
const LL mod=1004535809;
LL g=3;

LL Quick_Pow(LL a,LL b,LL p=mod) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)sum=sum*a%p;
	return sum;
}

LL inv(LL x) {
	return Quick_Pow(x,mod-2);
}

vector<int> ppt;

int find_root(LL x) {
	LL tmp=x-1;
	for(int i=2; i<=sqrt(tmp); i++)
		if(tmp%i==0) {
			ppt.push_back(i);
			while(tmp%i==0)tmp/=i;
		}
	for(int g=2; g<x; g++) {
		bool bj=1;
		for(int t:ppt)
			if(Quick_Pow(g,(x-1)/t,x)==1) {
				bj=0;
				break;
			}
		if(bj)return g;
	}
}

struct NumberTheoreticTransform {
	int n;
	LL omega[maxn],iomega[maxn];
	
	void init(int n) {
		this->n=n;
		int x=Quick_Pow(g,(mod-1)/n);
		omega[0]=iomega[0]=1;
		for(int i=1; i<n; i++) {
			omega[i]=omega[i-1]*x%mod;
			iomega[i]=inv(omega[i]);
		}
	}
	
	void transform(LL* a,LL* omega) {
		int k=log2(n);
		for(int i=0; i<n; i++) {
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=(1<<(k-j-1));
			if(i<t)swap(a[i],a[t]);
		}
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

void Multiply(const LL* a1,const int n1,const LL* a2,const int n2,LL* ans) {
	int n=1;
	while(n<n1+n2)n<<=1;
	ntt.init(n);
	static LL b1[maxn],b2[maxn];
	fill(b1,b1+n,0);
	fill(b2,b2+n,0);
	copy(a1,a1+n,b1);
	copy(a2,a2+n,b2);
	ntt.dft(b1);
	ntt.dft(b2);
	for(int i=0; i<n; i++)b1[i]=b1[i]*b2[i]%mod;
	ntt.idft(b1);
	for(int i=n1; i<=n1+n2; i++)b1[i-n1]=(b1[i-n1]+b1[i])%mod;
	for(int i=0; i<n1; i++)ans[i]=b1[i];
}

LL n,m,x,S,idx[maxn],f[maxn],ans[maxn];

int main() {
	// g=find_root(mod);
	n=Get_Int();
	m=Get_Int();
	x=Get_Int();
	S=Get_Int();
	LL g=find_root(m),tmp=1;
	for(int i=0; i<m-1; i++) {
		idx[tmp]=i;
		tmp=tmp*g%m;
	}
	for(int i=1; i<=S; i++) {
		int x=Get_Int();
		if(x==0)continue;
		f[idx[x]]=1;
	}
	ans[0]=1;
	for(; n; Multiply(f,m-1,f,m-1,f),n>>=1)
		if(n&1)Multiply(ans,m-1,f,m-1,ans);
	printf("%lld\n",ans[idx[x]]);
	return 0;
} 
