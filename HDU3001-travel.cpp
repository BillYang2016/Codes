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

const int maxn=15,maxs=60005;

int n,m,Pow[maxn];
LL f[maxn][maxs],mp[maxn][maxn];

int main() {
	Pow[0]=1;
	for(int i=1; i<=10; i++)Pow[i]=Pow[i-1]*3;
	while(~scanf("%d%d",&n,&m)) {
		memset(mp,0x3f,sizeof(mp));
		for(int i=1; i<=m; i++) {
			int x=Get_Int(),y=Get_Int();
			LL v=Get_Int();
			mp[x][y]=mp[y][x]=min(mp[x][y],v);
		}
		memset(f,0x3f,sizeof(f));
		for(int i=1; i<=n; i++)f[i][Pow[i-1]]=0;
		LL ans=0x3f3f3f3f3f3f3f3fll;
		for(int S=1; S<Pow[n]; S++) {
			for(int i=1; i<=n; i++)
				for(int j=1; j<=n; j++)if(i!=j&&(S/Pow[j-1])%3<2)f[j][S+Pow[j-1]]=min(f[j][S+Pow[j-1]],f[i][S]+mp[i][j]);
			bool bj=1;
			for(int i=1; i<=n; i++)if((S/Pow[i-1])%3==0)bj=0;
			if(bj)for(int i=1; i<=n; i++)ans=min(ans,f[i][S]);
		}
		printf("%lld\n",ans>=0x3f3f3f3f3f3f3f3fll?-1:ans);
	}
	return 0;
}