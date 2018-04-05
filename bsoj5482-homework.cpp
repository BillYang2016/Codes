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

const LL mod=1000000003;

int n,K;
LL f[55][2],a[55];

void add(LL &x,LL v) {x=x+v>=mod?x+v-mod:x+v;}

void Dp() {
	LL ans=0;
	for(int k=30; k>=0; k--) {
		memset(f,0,sizeof(f));
		f[n+1][0]=1;
		for(int i=n; i>=1; i--)
			if((a[i]>>k)&1) {
				add(f[i][0],f[i+1][0]*(1<<k)%mod); //chose 0
				add(f[i][1],f[i+1][1]*(1<<k)%mod);
				add(f[i][0],f[i+1][1]*((a[i]&((1<<k)-1))+1)%mod); //chose 1
				add(f[i][1],f[i+1][0]*((a[i]&((1<<k)-1))+1)%mod);
			} else {
				add(f[i][0],f[i+1][0]*((a[i]&((1<<k)-1))+1)%mod); //chose 0
				add(f[i][1],f[i+1][1]*((a[i]&((1<<k)-1))+1)%mod);
			}
		LL sum=1;
		bool now=K>>k&1;
		for(int i=1; i<=n; i++) {
			int lim=a[i]>>k&1;
			if(lim)add(ans,sum*f[i+1][now]%mod);
			now^=lim;
			sum=sum*((a[i]&((1<<k)-1))+1)%mod;
		}
		if(now==1)break;
		if(!k)add(ans,1);
	}
	printf("%lld\n",ans);
}

int main() {
	while(true) {
		n=Get_Int();
		K=Get_Int();
		if(n+K==0)break;
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		Dp();
	}
	return 0;
}