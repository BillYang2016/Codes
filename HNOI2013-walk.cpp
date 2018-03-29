#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=505,maxm=maxn*maxn/2;

int n,m,d[maxn];
double a[maxn][maxn],ans[maxm];
struct Edge {int from,to;} edges[maxm];

void Gauss_Jordan(int n,int m) {
	for(int i=1; i<=m; i++) {
		double t=a[i][i];
		for(int j=1; j<=m+1; j++)a[i][j]/=t;
		for(int j=1; j<=n; j++)
			if(j!=i) {
				t=a[j][i];
				for(int k=1; k<=m+1; k++)a[j][k]-=t*a[i][k];
			}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		edges[i].from=Get_Int();
		edges[i].to=Get_Int();
		d[edges[i].from]++;
		d[edges[i].to]++;
	}
	for(int i=1; i<=n; i++)a[i][i]=1;
	for(int i=1; i<=m; i++) {
		int x=edges[i].from,y=edges[i].to;
		if(x==n||y==n)continue;
		a[x][y]=-1.0/d[y];
		a[y][x]=-1.0/d[x];
	}
	a[1][n+1]=a[n][n+1]=1;
	Gauss_Jordan(n,n);
	for(int i=1; i<=m; i++) {
		if(edges[i].from!=n)ans[i]+=a[edges[i].from][n+1]/d[edges[i].from];
		if(edges[i].to!=n)ans[i]+=a[edges[i].to][n+1]/d[edges[i].to];
	}
	sort(ans+1,ans+m+1);
	double Ans=0;
	for(int i=1; i<=m; i++)Ans+=ans[i]*(m+1-i);
	printf("%0.3lf\n",Ans);
	return 0;
}