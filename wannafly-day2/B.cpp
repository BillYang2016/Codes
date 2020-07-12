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

const int maxn=55;
const LL mod=1e9+7;

int n,m;
LL f[maxn][maxn],lim[maxn],a[maxn];

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL Dp(int x,int y,int bit) {
	if(x==0&&y==0)return 1;
	if(x==0||y<0)return 0;
	if(~f[x][y])return f[x][y];
	return f[x][y]=(Dp(x-1,y,bit)*(1<<bit)%mod+Dp(x-1,y-1,bit)*(a[x]+1)%mod)%mod;
}

LL Cal(int bit) {
	if(bit<0)return 1;
	int cnt=0;
	LL others=1;
	for(int i=1; i<=n; i++) {
		if(lim[i]>>bit&1) {lim[i]^=1<<bit;a[++cnt]=lim[i];}
		else others=others*(lim[i]+1)%mod;
	}
	for(int i=1; i<=cnt; i++)
		for(int j=0; j<=cnt; j++)f[i][j]=-1;
	LL inv=Quick_Pow(1<<bit,mod-2),ans=0;
	for(int i=0; i<cnt; i++)if((m>>bit&1)==(i&1))ans=(ans+Dp(cnt,i,bit)*others%mod*inv%mod)%mod; //不全选1
	if((m>>bit&1)==(cnt&1))return (ans+Cal(bit-1))%mod; //全选1
	else return ans; //不能全选1
}

int main() {
	while(~scanf("%d%d",&n,&m)) {
		for(int i=1; i<=n; i++)lim[i]=Get_Int();
		printf("%lld\n",Cal(30));
	}
	return 0;
}