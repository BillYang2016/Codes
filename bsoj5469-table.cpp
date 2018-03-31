#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxm=10100005,mod=998244353;

int n,m,a,b,p,q;
int f[maxn],Powa[maxm],Powb[maxm],inv[maxm],inva[maxm];

int Down(int x,int y) {
	int ans=0,C=1;
	for(int i=0; i<=min(x-p,y-1); i++) {
		ans=(ans+1ll*f[y-i]*C%mod*Powa[x-p-i]%mod*Powb[i]%mod)%mod;
		C=1ll*C*(x-p-i)%mod*inv[i+1]%mod;
	}
	return ans;
}

int Up(int x,int y) {
	int ans=0,C=1;
	for(int i=y; i>=1; i--) {
		int t=(y-i)&1?mod-1:1;
		ans=(ans+1ll*t*Powb[y-i]%mod*inva[p-x+y-i]%mod*f[i]%mod*C%mod)%mod;
		C=1ll*C*(y-i+p-x)%mod*inv[y-i+1]%mod;
	}
	return ans;
}

int Quick_Pow(int a,int b) {
	int ans=1;
	for(; b; b>>=1,a=1ll*a*a%mod)if(b&1)ans=1ll*ans*a%mod;
	return ans;
}

int main() {
	m=Get_Int();
	n=Get_Int();
	Powa[1]=Get_Int();
	Powb[1]=Get_Int();
	Powa[0]=Powb[0]=inv[0]=inv[1]=inva[0]=1;
	inva[1]=Quick_Pow(Powa[1],mod-2);
	for(int i=2; i<=n+m; i++) {
		Powa[i]=1ll*Powa[i-1]*Powa[1]%mod;
		Powb[i]=1ll*Powb[i-1]*Powb[1]%mod;
		inva[i]=1ll*inva[i-1]*inva[1]%mod;
		inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
	}
	p=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)f[i]=Get_Int();
	while(q--) {
		int x=Get_Int(),y=Get_Int();
		printf("%d\n",x==p?f[y]:(x>p?Down(x,y):Up(x,y)));
	}
	return 0;
}