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

#define pii pair<LL,LL>
#define mp make_pair

const LL limit=1000000,hashmod=999959;

bool vst[limit+5];
int cnt=0,Prime[limit+5];
LL n,mod,Phi[limit+5],inv2,inv6;
vector<pii> Hash[hashmod+5];

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
	for(int i=2; i<=n; i++)Phi[i]=(Phi[i]+Phi[i-1])%mod;
}

void Add(int x,LL p,LL v) {
	Hash[x].push_back(mp(p,v));
}

LL Cal(LL n) {
	if(n<=limit)return Phi[n];
	for(pii x:Hash[n%hashmod])if(x.first==n)return x.second;
	LL next,ans=0;
	for(LL i=2; i<=n; i=next+1) {
		next=n/(n/i);
		ans=(ans+(next-i+1)%mod*Cal(n/i)%mod)%mod;
	}
	ans=(n%mod*(n%mod+1)%mod*inv2%mod-ans+mod)%mod;
	Add(n%hashmod,n,ans);
	return ans;
}

LL g(LL x) {return x*(x+1)%mod*(2*x+1)%mod*inv6%mod;}

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

int main() {
	n=Get_Int();
	mod=Get_Int();
	inv2=(mod+1)/2;
	inv6=Quick_Pow(6,mod-2);
	Table(min(n,limit));
	LL next=1,ans=0,last=0;
	for(int i=1; i<=n; i=next+1) {
		next=n/(n/i);
		LL now=Cal(next);
		ans=(ans+(now-last+mod)%mod*g(n/i)%mod)%mod;
		last=now;
	}
	printf("%lld\n",ans);
	return 0;
}