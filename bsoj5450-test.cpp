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

const int maxn=3005,maxs=1<<16;

int n,cnt=0,p[maxn],u[maxn];
LL f[maxs],g[maxs];
bool vst[maxn],sig[maxn];

void Mobius_Table(int n) {
	u[1]=1;
	for(int i=2; i<=n; i++) {
		if(!vst[i])p[++cnt]=i,u[i]=-1;
		for(int j=1; j<=cnt&&p[j]*i<=n; j++) {
			vst[p[j]*i]=1;
			if(i%p[j]==0) {u[p[j]*i]=0;break;}
			u[p[j]*i]=-u[i];
		}
	}
}

int Cal(int x,int k) {
	int ans=0;
	while(x) {ans+=x/k;x/=k;}
	return ans;
}

vector<int> a,vec[maxn];

int main() {
	n=Get_Int();
	Mobius_Table(n);
	for(int i=1; i<=cnt; i++)if(Cal(n,p[i])&1)a.push_back(p[i]),sig[i]=1;
	int t=sqrt(n),Max=0;
	for(int i=2; i<=n; i++)
		if(u[i]) {
			bool bj=1;
			for(int j=1; j<=cnt; j++)if(i%p[j]==0)bj&=sig[j];
			if(!bj)continue;
			int up=0,S=0;
			for(int j=0; j<a.size(); j++)
				if(i%a[j]==0) {
					if(a[j]>t)up=a[j];
					else S|=1<<j,Max=max(Max,j+1);
				}
			vec[up].push_back(S);
		}
	Max=1<<Max;
	f[0]=1;
	for(auto T:vec[0])
		for(int S=Max-1; S>=0; S--)
			if((S&T)==T)f[S]+=f[S^T];
	for(int i=1; i<=n; i++) { //只选一个
		if(vec[i].empty())continue;
		fill(g,g+Max,0);
		for(auto T:vec[i])
			for(int S=0; S<Max; S++)
				if((S&T)==T)g[S]+=f[S^T];
		copy(g,g+Max,f);
	}
	printf("%lld\n",f[Max-1]<<1);
	return 0;
}