#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=505,dx[]= {1,0,-1,0},dy[]= {0,1,0,-1};

int n,m;
char a[maxn][maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",a[i]+1);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			if(a[i][j]!='W')continue;
			for(int k=0; k<4; k++) {
				int nx=i+dx[k],ny=j+dy[k];
				if(nx<1||ny<1||nx>n||ny>m)continue;
				if(a[nx][ny]=='S') {puts("No");return 0;}
			}
		}
	puts("Yes");
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=m; j++)putchar(a[i][j]=='.'?'D':a[i][j]);
		putchar('\n');
	}
	return 0;
}