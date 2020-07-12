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

const int maxn=500005;
const LL mod=998244353;

struct Segment {int x,y,v;} a[maxn];

LL n,k,m,f[maxn],sum[maxn];
int One[maxn],Max[maxn];

LL Dp(int bit) {
	fill(One+1,One+n+2,0);
	fill(Max+1,Max+n+2,0);
	fill(f+1,f+n+2,0);
	fill(sum+1,sum+n+2,0);
	for(int i=1; i<=m; i++) {
		if(a[i].v>>bit&1)One[a[i].x]++,One[a[i].y+1]--;
		else Max[a[i].y]=max(Max[a[i].y],a[i].x);
	}
	for(int i=1; i<=n+1; i++)One[i]+=One[i-1],Max[i]=max(Max[i],Max[i-1]);
	f[0]=sum[0]=1;
	for(int i=1; i<=n+1; i++) {
		if(!One[i]) { //没有被1覆盖
			f[i]=sum[i-1];
			if(Max[i-1])f[i]-=sum[Max[i-1]-1];
			f[i]=(f[i]+mod)%mod;
		}
		sum[i]=(sum[i-1]+f[i])%mod;
	}
	return f[n+1];
}

int main() {
	n=Get_Int();
	k=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		a[i].x=Get_Int();
		a[i].y=Get_Int();
		a[i].v=Get_Int();
	}
	LL ans=1;
	for(int i=0; i<k; i++)ans=ans*Dp(i)%mod;
	printf("%lld\n",ans);
	return 0;
}