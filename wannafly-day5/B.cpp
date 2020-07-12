#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005;

int n,m,u[maxn],v[maxn],p[maxn],f[maxn],last[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++)u[i]=Get_Int(),v[i]=Get_Int();
	for(int i=1; i<=m; i++)p[i]=Get_Int();
	for(int i=1; i<=n; i++)f[i]=1;
	for(int i=m; i>=1; i--) {
		int x=u[p[i]],y=v[p[i]];
		last[p[i]]=f[x]=f[y]=f[x]+f[y]-last[p[i]];
	}
	for(int i=1; i<=n; i++)printf("%d%c",f[i],i==n?'\n':' ');
	return 0;
}