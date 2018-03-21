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

const int maxn=10000005;

int n,m,cnt=0,p[maxn];
bool vst[maxn];
LL f[maxn];

void Sieve(int n) {
	f[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {p[++cnt]=i;f[i]=i-1;}
		for(int j=1; j<=cnt&&i*p[j]<=n; j++) {
			vst[i*p[j]]=1;
			if(i%p[j]==0) {
				f[i*p[j]]=i%(p[j]*p[j])==0?0:-f[i]/(p[j]-1)*p[j];
				break;
			}
			f[i*p[j]]=f[i]*f[p[j]];
		}
	}
	for(int i=2; i<=n; i++)f[i]+=f[i-1];
}

int main() {
	Sieve(10000000);
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		LL ans=0;
		for(int i=1,next=0; i<=min(n,m); i=next+1) {
			next=min(n/(n/i),m/(m/i));
			ans+=(f[next]-f[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}