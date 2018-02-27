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

const int maxn=1000005;
const LL mod=1e9+7;

int vst[maxn],Prime[maxn],cnt=0; //prime
int Mobius[maxn]; //mobius
int t;
LL n,m,f[maxn],invf[maxn],g[maxn],sum[maxn],invsum[maxn];

void Mobius_Table(int n) {
	Mobius[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			Prime[++cnt]=i;
			Mobius[i]=-1;
		}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {
				Mobius[i*Prime[j]]=0;
				break;
			}
			Mobius[i*Prime[j]]=-Mobius[i];
		}
	}
}

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	while(b) {
		if(b&1)sum=sum*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return sum;
}

void initialize(int n) {
	Mobius_Table(n);
	f[1]=invf[1]=g[1]=1;
	for(int i=2; i<=n; i++) {
		g[i]=1;
		f[i]=(f[i-1]+f[i-2])%mod;
		invf[i]=Quick_Pow(f[i],mod-2);
	}
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j+=i) {
			if(Mobius[j/i]==1)g[j]=g[j]*f[i]%mod;
			if(Mobius[j/i]==-1)g[j]=g[j]*invf[i]%mod;
		}
	sum[0]=invsum[0]=1;
	for(int i=1; i<=n; i++)sum[i]=sum[i-1]*g[i]%mod,invsum[i]=Quick_Pow(sum[i],mod-2);
}

int main() {
	t=Get_Int();
	initialize(1000000);
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		int next;
		LL ans=1;
		for(int i=1; i<=min(n,m); i=next+1) {
			next=min(n/(n/i),m/(m/i));
			ans=ans*Quick_Pow(sum[next]*invsum[i-1]%mod,(n/i)*(m/i)%(mod-1))%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
} 
