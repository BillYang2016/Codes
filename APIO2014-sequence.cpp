#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=100005,maxk=2;

int n,m,Q[maxn];
LL sum[maxn],f[maxn][maxk];

double Slope(int i,int j,int con) {
	return (double)(f[i][con]-sum[i]*sum[n]-(f[j][con]-sum[j]*sum[n]))/(sum[i]-sum[j]);
}

int main() {
	n=Get_Int();
	m=Get_Int()+1;
	for(int i=1; i<=n; i++)sum[i]=sum[i-1]+Get_Int();
	for(int j=1; j<=m; j++) {
		int Left=1,Right=1;
		Q[1]=0;
		f[0][j&1]=0;
		for(int i=1; i<=n; i++) {
			while(Left<Right&&Slope(Q[Left],Q[Left+1],(j-1)&1)>=-sum[i])Left++;
			int Front=Q[Left];
			f[i][j&1]=f[Front][(j-1)&1]+(sum[i]-sum[Front])*(sum[n]-sum[i]);
			while(Left<Right&&Slope(Q[Right-1],Q[Right],(j-1)&1)<=Slope(Q[Right],i,(j-1)&1))Right--;
			Q[++Right]=i;
		}
	}
	printf("%lld\n",f[n][m&1]);
	return 0;
}