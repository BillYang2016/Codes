#include<bits/stdc++.h>

using namespace std;

const int maxn=1005;

int n,m;
double a[maxn][maxn][3],f[maxn][maxn];

int main() {
	while(~scanf("%d%d",&n,&m)) {
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++) {
				scanf("%lf%lf%lf",&a[i][j][0],&a[i][j][1],&a[i][j][2]);
				f[i][j]=0;
			}
		for(int i=n; i>=1; i--)
			for(int j=m; j>=1; j--) {
				if((i==n&&j==m)||fabs(a[i][j][0]-1)<=1e-5)continue;
				f[i][j]=(a[i][j][1]*f[i][j+1]+a[i][j][2]*f[i+1][j]+2)/(1-a[i][j][0]);
			}
		printf("%.3lf\n",f[1][1]);
	}
	return 0;
}