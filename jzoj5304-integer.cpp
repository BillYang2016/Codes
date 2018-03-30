#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define pii pair<LL,LL>

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int limit=10000000,maxn=limit+5,mod=1e9+7,hashmod=999599; 

int vst[maxn],u[maxn],p[maxn],cnt=0;
vector<pii> Hash[hashmod+5];

void Mobius_Table(int n) {
	u[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i]) {p[++cnt]=i;u[i]=-1;}
		for(int j=1; j<=cnt&&i*p[j]<=n; j++) {
			vst[i*p[j]]=1;
			if(i%p[j]==0) {u[i*p[j]]=0;break;}
			u[i*p[j]]=-u[i];
		}
	}
	for(int i=2; i<=n; i++)u[i]+=u[i-1];
}

void Add(int x,LL p,LL v) {Hash[x].push_back(pii(p,v));}

LL Cal(LL n) {
	if(n<=limit)return u[n];
	for(pii x:Hash[n%hashmod])if(x.first==n)return x.second;
	LL Next,ans=0;
	for(LL i=2; i<=n; i=Next+1) {
		Next=n/(n/i);
		ans+=(Next-i+1)*Cal(n/i);
	}
	ans=1-ans;
	Add(n%hashmod,n,ans);
	return ans;
}

LL n,k,fac[maxn],invf[maxn];

LL f(int x) { //\binom {x+k-1}{k}
	if(x+k-1<=limit)return fac[x+k-1]*invf[k]%mod*invf[x-1]%mod;
	LL ans=invf[k];
	for(int i=x; i<=x+k-1; i++)ans=ans*i%mod;
	return ans;
}

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)ans=ans*a%mod;
	return ans;
}

int main() {
	int t=Get_Int();
	n=limit;
	fac[0]=1;
	for(int i=1; i<=n; i++)fac[i]=fac[i-1]*i%mod;
	invf[n]=Quick_Pow(fac[n],mod-2);
	for(int i=n; i>=1; i--)invf[i-1]=invf[i]*i%mod;
	Mobius_Table(n);
	while(t--) {
		n=Get_Int();
		k=Get_Int();
		LL ans=0;
		for(int i=1,next; i<=n; i=next+1) {
			next=n/(n/i);
			ans=(ans+(Cal(next)-Cal(i-1)+mod)%mod*f(n/i)%mod)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}