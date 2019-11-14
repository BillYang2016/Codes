#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105,maxk=10005,mod=100000007;

int T,n,k,a[maxn],f[maxk];

int main() {
	T=Get_Int();
	for(int t=1; t<=T; t++) {
		n=Get_Int();
		k=Get_Int();
		for(int i=1; i<=n; i++)a[i]=Get_Int();
		fill(f,f+k+1,0);
		f[0]=1;
		for(int i=1; i<=n; i++)
			for(int j=a[i]; j<=k; j++)f[j]=(f[j]+f[j-a[i]])%mod;
		printf("Case %d: %d\n",t,f[k]);
	}
	return 0;
}