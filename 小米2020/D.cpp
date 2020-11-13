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

const int maxn=100005;
const LL mod=1e9+7;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

int n;
LL x,a[maxn],b[maxn];

int main() {
	while(scanf("%d%lld",&n,&x)!=EOF) {
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		for(int i=1; i<=n; i++)b[i]=Get_Int();
		LL ans=0;
		for(int i=1; i<=n; i++)ans=(ans+a[i]*b[i]%mod)%mod;
		ans=(ans*Quick_Pow(x,n-1)%mod+Quick_Pow(x,n))%mod;
		printf("%lld\n",ans);
	}
	return 0;
}