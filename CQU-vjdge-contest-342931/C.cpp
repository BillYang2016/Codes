#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

int T,n,sum[maxn],f[maxn][maxn];

int main() {
	T=Get_Int();
	for(int t=1; t<=T; t++) {
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			f[i][i]=Get_Int();
			sum[i]=sum[i-1]+f[i][i];
		}
		for(int len=2; len<=n; len++)
			for(int i=1; i+len-1<=n; i++) {
				int j=i+len-1;
				f[i][j]=sum[j]-sum[i-1];
				for(int k=i; k<j; k++)f[i][j]=max(f[i][j],max(sum[k]-sum[i-1]-f[k+1][j],sum[j]-sum[k]-f[i][k]));
			}
		printf("Case %d: %d\n",t,f[1][n]);
	}
	return 0;
}