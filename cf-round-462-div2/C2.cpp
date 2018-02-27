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

const int maxn=2005;

int n,a[maxn],f[maxn][3],g[maxn][3],t[maxn][maxn][3][3],tmp[maxn][3];

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		if(a[i]==2)f[i][2]=max(f[i][2],max(f[i-1][1],f[i-1][2])+1);
		else f[i][1]=max(f[i][1],f[i-1][1]+1);
		f[i][1]=max(f[i][1],f[i-1][1]);
		f[i][2]=max(f[i][2],max(f[i-1][1],f[i-1][2]));
	}
	for(int j=1; j<=n; j++) {
		memset(tmp,0,sizeof(tmp));
		tmp[j-1][2]=-INT_MAX;
		for(int i=j; i<=n; i++) {
			if(a[i]==2)tmp[i][2]=max(tmp[i][2],max(tmp[i-1][1],tmp[i-1][2])+1);
			else tmp[i][1]=max(tmp[i][1],tmp[i-1][1]+1);
			tmp[i][1]=max(tmp[i][1],tmp[i-1][1]);
			tmp[i][2]=max(tmp[i][2],max(tmp[i-1][1],tmp[i-1][2]));
		}
		g[j][1]=max(tmp[n][1],tmp[n][2]);
		memset(tmp,0,sizeof(tmp));
		tmp[j-1][1]=-INT_MAX;
		for(int i=j; i<=n; i++) {
			if(a[i]==2)tmp[i][2]=max(tmp[i][2],tmp[i-1][2]+1);
			else tmp[i][2]=max(tmp[i][2],tmp[i-1][2]);
		}
		g[j][2]=tmp[n][2];
	}
	for(int j=1; j<=n; j++) {
		memset(tmp,0,sizeof(tmp));
		tmp[j+1][2]=-INT_MAX;
		for(int i=j; i>=1; i--) {
			if(a[i]==2)tmp[i][2]=max(tmp[i][2],max(tmp[i+1][1],tmp[i+1][2])+1);
			else tmp[i][1]=max(tmp[i][1],tmp[i+1][1]+1);
			tmp[i][1]=max(tmp[i][1],tmp[i+1][1]);
			tmp[i][2]=max(tmp[i][2],max(tmp[i+1][1],tmp[i+1][2]));
			t[i][j][1][1]=tmp[i][1],t[i][j][1][2]=tmp[i][2];
		}
		memset(tmp,0,sizeof(tmp));
		f[j+1][1]=-INT_MAX;
		for(int i=j; i>=1; i--) {
			if(a[i]==2)tmp[i][2]=max(tmp[i][2],tmp[i+1][2]+1);
			else tmp[i][2]=max(tmp[i][2],tmp[i+1][2]);
			t[i][j][2][2]=tmp[j][2];
		}
	}
	int ans=0;
	for(int i=1; i<=n; i++)
		for(int j=i; j<=n; j++)
			ans=max(max(ans,f[i-1][2]+t[i][j][2][2]+g[j+1][2]),max(f[i-1][1]+t[i][j][1][1]+g[j+1][1],f[i-1][1]+t[i][j][1][2]+g[j+1][2]));
	printf("%d\n",ans);
	return 0;
}