#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=265;

int n,m,k;
char s[maxn];
bitset<maxn> a[maxn<<1],f[maxn][maxn];

bool Gauss(int n) {
	int now=0;
	for(int i=1; i<=m; i++) {
		int row=now+1;
		for(; row<=n; row++)if(a[row][i])break;
		if(row>n)continue;
		now++;
		swap(a[now],a[row]);
		for(int j=1; j<=n; j++)if(now!=j&&a[j][i])a[j]^=a[now];
	}
	for(int i=now+1; i<=n; i++)if(a[i][m+1])return 0;
	return 1;
}

bool Solve() {
	for(int i=1; i<=m; i++)f[1][i].reset(),f[1][i].flip(i);
	for(int i=2; i<=n+1; i++)
		for(int j=1; j<=m; j++) {
			f[i][j]=f[i-1][j-1]^f[i-1][j]^f[i-1][j+1]^f[i-2][j];
			f[i][j][m+1]=f[i][j][m+1]^a[i-1][j];
		}
	int cnt=0;
	for(int i=1; i<=k; i++) {
		int x=Get_Int(),y=Get_Int();
		a[++cnt]=f[x][y];
	}
	for(int i=1; i<=m; i++)a[++cnt]=f[n+1][i];
	return Gauss(cnt);
}

int main() {
	int T=Get_Int();
	for(int t=1; t<=T; t++) {
		n=Get_Int();
		m=Get_Int();
		k=Get_Int();
		for(int i=1; i<=n; i++) {
			scanf("%s",s+1);
			for(int j=1; j<=m; j++)
				if(s[j]=='B')a[i][j]=1;
				else a[i][j]=0;
		}
		printf("Case #%d:\n",t);
		puts(Solve()?"YES":"NO");
	}
	return 0;
}