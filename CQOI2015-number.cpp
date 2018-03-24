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

int n,k,d,u,tmp=0;
LL f[maxn];

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

int main() {
	n=Get_Int();
	k=Get_Int();
	d=Get_Int();
	u=Get_Int();
	if(d<=k&&k<=u)tmp=1;
	d=(d-1)/k,u/=k;
	int len=u-d;
	for(int i=len; i>=1; i--) {
		int x=d/i,y=u/i;
		f[i]=((Quick_Pow(y-x,n)-y+x)%mod+mod)%mod;
		for(int j=i<<1; j<=len; j+=i)f[i]=(f[i]-f[j]+mod)%mod;
	}
	printf("%lld\n",f[1]+tmp);
	return 0;
}