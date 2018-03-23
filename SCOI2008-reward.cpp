#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=55,maxm=16,maxs=1<<15;

int n,m,a[maxm],pre[maxm];
double f[maxn][maxs];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		a[i]=Get_Int();
		int x;
		while(x=Get_Int())pre[i]|=1<<(x-1);
	}
	for(int i=n; i>=1; i--)
		for(int S=0; S<(1<<m); S++) {
			for(int j=1; j<=m; j++)
				if((pre[j]&S)==pre[j])f[i][S]+=max(f[i+1][S],f[i+1][S|(1<<(j-1))]+a[j]);
				else f[i][S]+=f[i+1][S];
			f[i][S]/=m;
		}
	printf("%0.6lf\n",f[1][0]);
	return 0;
}