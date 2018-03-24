#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int dx[]= {0,1,-1,0,0},dy[]= {0,0,0,1,-1};

int n,m;
bool ans[1605];
bitset<1605> a[1605];

void Gauss(int n) {
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(a[row][i])break;
		if(row>n)continue;
		swap(a[i],a[row]);
		for(int j=i+1; j<=n; j++)if(j!=i&&a[j][i])a[j]^=a[i];
	}
	for(int i=n; i>=1; i--) {
		ans[i]=a[i][i]?a[i][n+1]:1;
		if(ans[i])for(int j=1; j<i; j++)if(a[j][i])a[j].flip(n+1);
	}
}

int id(int x,int y) {return (x-1)*m+y;}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			for(int k=0; k<=4; k++) {
				int nx=i+dx[k],ny=j+dy[k];
				if(nx<1||ny<1||nx>n||ny>m)continue;
				a[id(i,j)][id(nx,ny)]=1;
			}
	Gauss(n*m);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)printf("%d%c",ans[id(i,j)],j==m?'\n':' ');
	return 0;
}