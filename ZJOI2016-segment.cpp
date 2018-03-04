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

const int maxn=405,p=1e9+7;
int n,q,a[maxn],f[2][maxn][maxn],sum1[2][maxn][maxn],sum2[2][maxn][maxn],g[maxn][maxn];

int main() {
	n=Get_Int();
	q=Get_Int();
	a[0]=a[n+1]=INT_MAX/2;
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		int Max=0;
		for(int j=i; j<=n; j++) {
			g[i][j]=(i*(i-1)>>1)+((n-j+1)*(n-j)>>1)+((j-i+2)*(j-i+1)>>1);
			Max=max(Max,a[j]);
			if(i==1&&j==n)f[0][i][j]=Max;
			else if(a[i-1]>Max&&a[j+1]>Max)f[0][i][j]=(Max-min(a[i-1],a[j+1])+p)%p;
		}
	}
	int now=0,pre=1;
	for(int i=1; i<=q; i++) {
		swap(now,pre);
		for(int j=1; j<=n; j++)
			for(int k=n; k>=j; k--)
				sum2[pre][j][k]=(sum2[pre][j][k+1]+1ll*f[pre][j][k]*(n-k))%p;
		for(int j=1; j<=n; j++)
			for(int k=j; k<=n; k++) {
				sum1[pre][j][k]=(sum1[pre][j-1][k]+1ll*f[pre][j][k]*(j-1))%p;
				f[now][j][k]=(1ll*f[pre][j][k]*g[j][k]+sum1[pre][j-1][k]+sum2[pre][j][k+1])%p;
			}
	}
	for(int i=1; i<=n; i++) {
		int sum=0;
		for(int j=1; j<=i; j++)
			for(int k=i; k<=n; k++)sum=(sum+f[q&1][j][k])%p;
		printf("%d ",sum);
	}
	return 0;
}