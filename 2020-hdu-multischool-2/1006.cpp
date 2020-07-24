#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef unsigned long long LL;

const int maxn=2000005;

int n,m,k;
LL f[maxn];

int main() {
	int t=Get_Int();
	f[1]=1;
	f[2]=2;
	for(int i=3; i<=2000000; i++)f[i]=f[i-1]+f[i-2];
	while(t--) {
		n=Get_Int();
		LL a=0,b=0,c=0,d=0;
		for(int i=1; i<=n; i++) {
			int x=Get_Int();
			if(x)a+=f[i];
		}
		m=Get_Int();
		for(int i=1; i<=m; i++) {
			int x=Get_Int();
			if(x)b+=f[i];
		}
		k=Get_Int();
		c=a*b;
		for(int i=1; i<=k; i++) {
			int x=Get_Int();
			if(x)d+=f[i];
		}
		for(int i=1; i<=max(k,n+m); i++)if(d+f[i]==c) {printf("%d\n",i);break;}
	}
	return 0;
}