#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,mod=1e9+7;

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

int n,m,k,a[maxn];
LL ans=0,Degree[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		Degree[x]++,Degree[y]++;
	}
	for(int i=1; i<=n; i++)ans=(ans+Degree[i]*a[i]%mod*k%mod)%mod;
	printf("%lld\n",ans*Quick_Pow(2*m%mod,mod-2)%mod);
	return 0;
}