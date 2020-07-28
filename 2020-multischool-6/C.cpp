#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=205;

int n,m,a[maxn][maxn],sum[maxn][maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		double ans=0;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=m; j++) {
				a[i][j]=Get_Int();
				sum[i][j]=sum[i-1][j]+a[i][j];
				ans=max(ans,1.0*sum[i][j]/a[i][j]);
			}
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}