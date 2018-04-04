#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=35,maxs=1<<8,mod=12345678,dx[]= {-1,0,1,1,1,0,-1,-1},dy[]= {1,1,1,0,-1,-1,-1,0};

int n,m,a[5][10],f[maxn][maxs],rem[maxs];
char mp[5][10];
bool vst[5][10];

#define pii pair<int,int>

void add(int &x,int v) {x+=v;if(x>=mod)x-=mod;}

int Dp() {
	vector<pii> put;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(a[i][j])put.push_back(pii(i,j));
	int cnt=put.size();
	for(int S=0; S<(1<<cnt); S++) {
		rem[S]=n*m-cnt;
		memset(vst,0,sizeof(vst));
		for(int i=0; i<cnt; i++)if(!((S>>i)&1)) {
			int x=put[i].first,y=put[i].second;
			for(int k=0; k<8; k++) {
				int nx=x+dx[k],ny=y+dy[k];
				if(nx<1||nx>n||ny<1||ny>m)continue;
				if(!vst[nx][ny])rem[S]--,vst[nx][ny]=1;
			}
		}
	}
	memset(f,0,sizeof(f));
	f[0][0]=1;
	for(int i=0; i<n*m; i++)
		for(int S=0; S<(1<<cnt); S++)if(f[i][S]) {
			int tot=0;
			for(int T=S; T; T-=T&(-T))tot++;
			for(int j=0; j<cnt; j++)if(!((S>>j)&1))add(f[i+1][S|(1<<j)],f[i][S]);
			add(f[i+1][S],1ll*f[i][S]*(rem[S]-(i-tot))%mod);
		}
	return f[n*m][(1<<cnt)-1];
}

int ans=0;

void Dfs(int x,int y,int f) { //f容斥系数
	if(y>m) {Dfs(x+1,1,f);return;}
	if(x>n) {add(ans,f==1?f*Dp():f*Dp()+mod);return;}
	Dfs(x,y+1,f);
	if(!a[x][y]) {
		bool bj=1;
		for(int i=0; i<8; i++) {
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<1||nx>n||ny<1||ny>m)continue;
			if(a[nx][ny]) {bj=0;break;}
		}
		if(bj) {a[x][y]=1;Dfs(x,y+1,-f);a[x][y]=0;}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",mp[i]+1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)a[i][j]=mp[i][j]=='X';
	bool bj=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)if(a[i][j])
			for(int k=0; k<8; k++) {
				int nx=i+dx[k],ny=j+dy[k];
				if(nx<1||nx>n||ny<1||ny>m)continue;
				if(a[nx][ny]) {puts("0");return 0;}
			}
	ans=0;
	Dfs(1,1,1);
	printf("%d\n",ans);
	return 0;
}