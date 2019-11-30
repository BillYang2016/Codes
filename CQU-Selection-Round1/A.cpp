#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define pii pair<int,int>
#define mp make_pair

const int dx[]= {0,1,1,2,2,-1,-1,-2,-2},dy[]= {0,2,-2,1,-1,2,-2,1,-1};
int n,m,x,y,f[505][505];
bool vst[505][505];

void Bfs() {
	queue<pii> Q;
	Q.push(mp(x,y));
	vst[x][y]=1;
	while(!Q.empty()) {
		pii Now=Q.front();
		Q.pop();
		for(int i=1; i<=8; i++) {
			pii Next=mp(Now.first+dx[i],Now.second+dy[i]);
			if(Next.first<1||Next.first>n||Next.second<1||Next.second>m||vst[Next.first][Next.second])continue;
			Q.push(Next);
			vst[Next.first][Next.second]=1;
			f[Next.first][Next.second]=f[Now.first][Now.second]+1;
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	x=Get_Int();
	y=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)f[i][j]=-1;
	f[x][y]=0;
	Bfs();
	for(int i=1; i<=n; i++) {
		for(int j=1; j<m; j++)printf("%d\t",f[i][j]);
		printf("%d\n",f[i][m]);
	}
	return 0;
}