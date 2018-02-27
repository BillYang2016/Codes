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

const int maxn=55;

int n;
double a[maxn][maxn],ans=1;

void Gauss_Jordan(int n) {
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(fabs(a[row][i])>eps)break;
		if(row>n)continue;
		if(row!=i)for(int j=1; j<=n+1; j++)swap(a[i][j],a[row][j]);
		double t=a[i][i];
		for(int j=1; j<=n+1; j++)a[i][j]/=t;
		for(int j=1; j<=n; j++)
			if(j!=i) {
				t=a[j][i];
				for(int k=1; k<=n+1; k++)a[j][k]-=t*a[i][k];
			}
		ans*=a[i][i];
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++) {
			scanf("%lf",&a[i][j]);
			if(i==j)continue;
			if(i<j)ans*=1-a[i][j];
			a[i][j]/=1-a[i]][j];
		}
	n--;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			if(i!=j)a[i][i]+=a[i][j],a[i][j]=-a[i][j];
	Gauss_Jordan();
	printf("%0.10lf\n",ans);
	return 0;
}