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
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=100005,maxb=256;

int n,type,f[maxn][maxb],g[maxn][maxb];
char opt[5];

int Cal(int x,int y) {
	if(opt[0]=='a')return x&y;
	if(opt[0]=='o')return x|y;
	return x^y;
}

int main() {
	n=Get_Int();
	scanf("%s",opt);
	type=Get_Int();
	for(int i=1; i<=n; i++) {
		int v=Get_Int();
		int l=(v>>8),r=v^(l<<8),Max=-INT_MAX,sum=0;
		for(int j=0; j<maxb; j++)
			if(g[j][r]) {
				int now=(Cal(l,j)<<8)|f[j][r];
				if(now>Max) {
					Max=now;
					sum=g[j][r];
				} else if(now==Max)sum+=g[j][r];
			}
		for(int j=0; j<maxb; j++) {
			int now=Cal(j,r);
			if(!g[l][j]||now>f[l][j]) {
				f[l][j]=now;
				g[l][j]=1;
			} else if(now==f[l][j])g[l][j]++;
		}
		if(i==1)continue;
		if(!type)printf("%d\n",Max);
		else printf("%d %d\n",Max,sum);
	}
	return 0;
} 
