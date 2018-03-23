#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=1000005;

int n,m;
double p[maxn],f[2],sum0,sum1,last0,last1;

int main() {
	n=Get_Int();
	m=Get_Int();
	p[1]=1;
	for(int i=2; i<=n; i++)p[i]=p[i-1]/m;
	for(int i=2; i<=n; i++)p[i]*=i;
	for(int i=1; i<n; i++) {
		f[0]=p[i]*i*(m-1)/m+sum0*(m-2)/m+sum1*(m-1)/m;
		f[1]=sum0/m;
		sum0=(sum0+last0)/m+f[0];
		sum1=(sum1+last1)/m+f[1];
		last0=last0/m+f[0];
		last1=last1/m+f[1];
	}
	printf("%0.5lf\n",sum0+p[n]);
	return 0;
}