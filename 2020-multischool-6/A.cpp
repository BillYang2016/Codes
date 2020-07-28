#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const LL mod=998244353;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL inv(LL x) {return Quick_Pow(x,mod-2);}

const int maxn=100005;

int n,a[maxn];
LL f[maxn],sum[maxn];
bool vst[maxn];

int main() {
	n=Get_Int();
	int t=Get_Int();
	f[1]=0;
	for(int i=2; i<=n; i++) {
		f[i]=(sum[i-1]*inv(i)%mod+1)%mod*i%mod*inv(i-1)%mod;
		sum[i]=(sum[i-1]+f[i])%mod;
	}
	while(t--) {
		for(int i=1; i<=n; i++)a[i]=Get_Int(),vst[i]=0;
		LL ans=0;
		for(int i=1; i<=n; i++) {
			int x=i,size=0;
			while(!vst[x]) {
				vst[x]=1;
				x=a[x];
				size++;
			}
			if(size)ans=(ans+f[size]*size%mod)%mod;
		}
		printf("%lld\n",ans%mod);
	}
	return 0;
}