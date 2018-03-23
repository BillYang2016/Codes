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

int n,m;
double p[maxn],f[maxn][2];

int main() {
	n=Get_Int();
	m=Get_Int();
	p[1]=1;
	for(int i=2; i<=n; i++)p[i]=p[i-1]/m;
	f[0][1]=1;
	for(int i=0; i<=n; i++)
		for(int j=i+1; j<=n; j++) {
			f[j][0]+=(j-i)*p[j-i]*(f[i][0]*(m-2)/m+f[i][1]*(m-1)/m);
			f[j][1]+=(j-i)*p[j-i]*f[i][0]/m;
		}
	double ans=p[n]*n;
	for(int i=1; i<n; i++)ans+=i*i*p[i]*f[n-i][0];
	printf("%0.5lf\n",ans);
	return 0;
}