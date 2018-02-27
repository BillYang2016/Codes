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

namespace FastIO {
	const int L=1<<15;
	char buf[L],*S,*T;
	char getchar() {
		if(S==T){T=(S=buf)+fread(buf,1,L,stdin);if(S==T)return EOF;}
		return *S++;
	}
	LL Get_Int() {
		LL res=0,bj=1;char c=getchar();
		while(!isdigit(c)) {if(c=='-')bj=-1;c=getchar();}
		while(isdigit(c)) {res=res*10+c-'0';c=getchar();}
		return res*bj;
	}
}
using FastIO::Get_Int;	

const int maxn=1000005;

LL n;
int cnt=0,Prime[maxn],Phi[maxn];
bool vst[maxn]; 

void Table(int n) {
	Phi[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {
			Prime[++cnt]=i;
			Phi[i]=i-1;
		}
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0) {
				Phi[i*Prime[j]]=Phi[i]*Prime[j];
				break;
			}
			Phi[i*Prime[j]]=Phi[i]*Phi[Prime[j]];
		}
	}
}

int main() {
	Table(1000000);
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		LL ans=0;
		for(int i=1; i<=sqrt(n); i++)
			if(n%i==0) {
				if(i!=1)ans+=(LL)i*Phi[i]/2;
				else ans++;
				if(n/i!=i)ans+=(LL)(n/i)*Phi[n/i]/2;
			}
		printf("%lld\n",ans*n);
	}
	return 0;
} 
