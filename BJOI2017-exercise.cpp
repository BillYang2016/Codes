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

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=35,mod=1e9+9;

struct pii {
	int x,y;
	pii(int x=0,int y=0):x(x),y(y) {}
};

int n,m,f[maxn][maxn][maxn][maxn],g[3][3][3][3],ans=0;
char map[maxn][maxn];
vector<pii> dxy1,dxy2;

void add(int &x,int v) {
	x+=v;
	if(x>=mod)x-=mod;
}

int Dp(int x1,int y1,int x2,int y2) {
	if(x1<1||x1>n||y1<1||y1>m||x2<1||x2>n||y2<1||y2>m||map[x1][y1]!=map[x2][y2])return 0;
	if(~f[x1][y1][x2][y2])return f[x1][y1][x2][y2];
	f[x1][y1][x2][y2]=1;
	for(pii d1:dxy1)for(pii d2:dxy2)add(f[x1][y1][x2][y2],Dp(x1+d1.x,y1+d1.y,x2+d2.x,y2+d2.y));
	return f[x1][y1][x2][y2];
}

int Solve(int dx1,int dy1,int dx2,int dy2) {
	if(~g[dx1+1][dy1+1][dx2+1][dy2+1])return g[dx1+1][dy1+1][dx2+1][dy2+1];
	dxy1.clear(),dxy2.clear();
	for(int i=-1; i<=1; i++) {
		if(i&&i!=dx1)continue;
		for(int j=-1; j<=1; j++) {
			if((!i&&!j)||(j&&j!=dy1))continue;
			dxy1.push_back(pii(i,j));
		}
	}
	for(int i=-1; i<=1; i++) {
		if(i&&i!=dx2)continue;
		for(int j=-1; j<=1; j++) {
			if((!i&&!j)||(j&&j!=dy2))continue;
			dxy2.push_back(pii(i,j));
		}
	}
	memset(f,-1,sizeof(f));
	int sum=0;
	for(int sx1=1; sx1<=n; sx1++)
		for(int sy1=1; sy1<=m; sy1++)
			for(int sx2=1; sx2<=n; sx2++)
				for(int sy2=1; sy2<=m; sy2++)
					add(sum,Dp(sx1,sy1,sx2,sy2));
	g[dx1+1][dy1+1][dx2+1][dy2+1]=g[dx2+1][dy2+1][dx1+1][dy1+1]=g[-dx1+1][-dy1+1][-dx2+1][-dy2+1]=g[-dx2+1][-dy2+1][-dx1+1][-dy1+1]=sum;
	return sum;
}

int Solve(int x,int y) {
	int sum=0;
	add(sum,Solve(-1,-1,x,y));
	add(sum,Solve(-1,1,x,y));
	add(sum,Solve(1,-1,x,y));
	add(sum,Solve(1,1,x,y));
	add(sum,mod-Solve(-1,0,x,y));
	add(sum,mod-Solve(1,0,x,y));
	add(sum,mod-Solve(0,-1,x,y));
	add(sum,mod-Solve(0,1,x,y));
	return sum;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",map[i]+1);
	memset(g,-1,sizeof(g));
	add(ans,Solve(-1,-1));
	add(ans,Solve(-1,1));
	add(ans,Solve(1,-1));
	add(ans,Solve(1,1));
	add(ans,mod-Solve(-1,0));
	add(ans,mod-Solve(1,0));
	add(ans,mod-Solve(0,-1));
	add(ans,mod-Solve(0,1));
	printf("%d\n",ans);
	return 0;
}