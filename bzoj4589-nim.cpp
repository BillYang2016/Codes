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

const int maxn=1<<16,maxm=50005;
const int mod=1e9+7,inv2=5e8+4;

struct FastWalshTransform {
	int n;
	void init(int n) {
		this->n=n;
	}
	void transform(LL *a,LL mul) {
		for(int len=2; len<=n; len<<=1) {
			int mid=len>>1;
			for(LL *p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					LL x=p[i],y=p[mid+i];
					p[i]=(x+y)*mul%mod;
					p[mid+i]=(x-y+mod)*mul%mod;
				}
		}
	}
	void fwt(LL *a) {
		transform(a,1);
	}
	void ufwt(LL *a) {
		transform(a,inv2);
	}
} wtf;

LL a[maxn],b[maxn];
int n,m,Prime[maxn],cnt=0;
bool vst[maxm];

void Prime_Table(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i])Prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
}

int main() {
	Prime_Table(50000);
	while(~scanf("%d%d",&n,&m)) {
		int t=1;
		while(t<=m)t<<=1;
		wtf.init(t);
		fill(a,a+t,0),fill(b,b+t,0);
		for(int i=1; i<=cnt&&Prime[i]<=m; i++)a[Prime[i]]=1;
		b[0]=1;
		wtf.fwt(a),wtf.fwt(b);
		for(; n; n>>=1) {
			if(n&1)for(int i=0; i<t; i++)b[i]=a[i]*b[i]%mod;
			for(int i=0; i<t; i++)a[i]=a[i]*a[i]%mod;
		}
		wtf.ufwt(b);
		printf("%lld\n",b[0]);
	}
	return 0;
}