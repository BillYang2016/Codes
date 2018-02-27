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

#define lowbit(x) ((x)&(-(x)))

const int maxs=(1<<17)+5;

int n,m;
LL Pow[maxs],In[maxs],Out[maxs],bitcnt[maxs],f[maxs];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=1<<(Get_Int()-1),y=1<<(Get_Int()-1);
		Out[x]|=y;
		In[y]|=x;
	}
	Pow[0]=1;
	for(int i=1; i<=n*n; i++)Pow[i]=(Pow[i-1]<<1)%mod;
	bitcnt[0]=0;
	for(int i=1; i<(1<<n); i++)bitcnt[i]=bitcnt[i^lowbit(i)]+1;
	f[0]=1;
	for(int S=1; S<(1<<n); S++)
		for(int T=S; T; T=(T-1)&S) {
			if(T!=S) {
				int u=lowbit(S^T);
				p[T]=p[T^u]+bitcnt[Out[u]&T]-bitcnt[In[u]&(S^T)];
			} else p[T]=0;
			if(bitcnt[T]&1)f[S]=(f[S]+f[S^T]*Pow[p[T]]%mod)%mod;
			else f[S]=(f[S]-f[S^T]*Pow[p[T]]%mod+mod)%mod;
		}
	printf("%lld\n",f[(1<<n)-1]);
	return 0;
} 
