#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=15;

int n,m,state[1<<maxn],Pow[maxn],pre[maxn],f[14348907],trans[1<<maxn][maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1,x,last=0; i<=m; i++)x=Get_Int(),pre[x]=last,last=x;
	Pow[0]=1;
	for(int i=1; i<n; i++)Pow[i]=Pow[i-1]*3;
	for(int S=0; S<(1<<n); S++)
		for(int i=1; i<=n; i++)
			if(!(S>>(i-1)&1)) {
				trans[S][i]=S|(1<<(i-1));
				for(int j=i+1; j<=n; j++)if(S>>(j-1)&1) {trans[S][i]^=1<<(j-1);break;}
			} else state[S]+=Pow[i-1];
	for(int i=1; i<=n; i++)if(pre[i]==0)f[Pow[i-1]<<1]=1;
	for(int S=1; S<(1<<n); S++)
		for(int i=1; i<=n; i++)
			if(!(S>>(i-1)&1)) {
				if(pre[i]&&!(S>>(pre[i]-1)&1))continue;
				for(int T=S; T; T=(T-1)&S)f[state[S|(1<<(i-1))]+state[trans[T][i]]]+=f[state[S]+state[T]];
			}
	int ans=0;
	for(int i=1; i<(1<<n); i++)if(__builtin_popcount(i)==m)ans+=f[state[(1<<n)-1]+state[i]];
	printf("%d\n",ans);
	return 0;
}