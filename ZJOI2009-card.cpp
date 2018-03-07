#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=17,maxs=1<<16,mod=19901013;

int n,m,a[maxn][maxn],bit[maxn],bitnum[maxs],f[maxn][maxn][maxs],g[maxn],h[maxn][maxn][maxn][maxn],ans=0;

void check(int &x) {if(x>=mod)x-=mod;if(x<0)x+=mod;}
void add(int &x,int v) {x+=v;check(x);}
void mul(int &x,int v) {x=1ll*x*v%mod;}

void Dp() {
	for(int u=1; u<=n; u++)
		for(int l=1; l<=m; l++)
			for(int r=l; r<=m; r++) {
				int lim=bit[r-l+1];
				for(int S=0; S<lim; S++)f[u][l][S]=0;
				f[u][l][0]=1;
				for(int x=u; x<=n; x++) {
					for(int y=l; y<r; y++) { //<r
						for(int S=0; S<lim; S++)f[x][y+1][S]=0;
						for(int S=0; S<lim; S++)
							if(f[x][y][S]) {
								add(f[x][y+1][S&(~bit[y-l])],f[x][y][S]); //不放
								if(y>l&&a[x][y-1]&&a[x][y]&&!(S&bit[y-l-1]))add(f[x][y+1][S|bit[y-l]|bit[y-l-1]],f[x][y][S]); //横放
								if(x>u&&a[x-1][y]&&a[x][y]&&!(S&bit[y-l]))add(f[x][y+1][S|bit[y-l]],f[x][y][S]); //竖放
							}
					}
					//==r
					for(int S=0; S<lim; S++)f[x+1][l][S]=0;
					for(int S=0; S<lim; S++)
						if(f[x][r][S]) {
							add(f[x+1][l][S&(~bit[r-l])],f[x][r][S]);
							if(r>l&&a[x][r-1]&&a[x][r]&&!(S&bit[r-l-1]))add(f[x+1][l][S|bit[r-l]|bit[r-l-1]],f[x][r][S]); //横放
							if(x>u&&a[x-1][r]&&a[x][r]&&!(S&bit[r-l]))add(f[x+1][l][S|bit[r-l]],f[x][r][S]); //竖放
						}
					for(int S=0; S<lim; S++)add(h[u][x][l][r],f[x+1][l][S]);
				}
			}
}

char s[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=0; i<=max(n,m); i++)bit[i]=1<<i;
	for(int i=1; i<=n; i++) {
		scanf("%s",s+1);
		for(int j=1; j<=m; j++)
			if(s[j]=='.')a[i][j]=1;
			else a[i][j]=0;
	}
	Dp();
	for(int S=0; S<bit[m]; S++)bitnum[S]=bitnum[S>>1]+(S&1);
	for(int S=0; S<bit[m-1]; S++) {
		memset(g,0,sizeof(g));
		g[0]=1;
		vector<int> c;
		for(int i=1; i<m; i++)if(S&bit[i-1])c.push_back(i);
		for(int u=1; u<=n; u++)
			for(int x=0; x<u; x++) {
				int now=1,l=1;
				for(int r:c) {
					mul(now,h[x+1][u][l][r]);
					l=r+1;
				}
				if(l<=m)mul(now,h[x+1][u][l][m]);
				if(x>0)add(g[u],mod-1ll*g[x]*now%mod);
				else add(g[u],1ll*g[x]*now%mod);
			}
		if(bitnum[S]&1)add(ans,mod-g[n]);
		else add(ans,g[n]);
	}
	printf("%d\n",ans);
	return 0;
}