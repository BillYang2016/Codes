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

const int maxn=300005;

LL fac[maxn],inv[maxn],f[maxn];

LL C(int n,int m) {
	return fac[n]*inv[n-m]%mod*inv[m]%mod;
}

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)Hash[Get_Int()]++;
	fac[0]=inv[0]=inv[1]=1;
	for(int i=1; i<=n; i++) {
		fac[i]=fac[i-1]*i;
		if(i!=1)inv[i]=(p-p/i)*inv[p%i]%p;
	}
	for(int i=1; i<=m; i++) {
		int cnt=0;
		for(int j=1; (LL)i*j<=m; j++)cnt+=Hash[i*j];
		if(cnt<n-k)continue; //无解
		f[i]=C(cnt,n-k)*Quick_Pow(m/i-1,cnt-(n-k))%mod*Quick_Pow(m/i,n-cnt)%mod;
	}
	for(int i=m; i>=1; i--)
		for(int j=2; (LL)i*j<=m; j++)f[i]=(f[i]-f[i*j])%mod;
	for(int i=1; i<=m; i++)printf("%d ",f[i]);
	return 0;
} 
