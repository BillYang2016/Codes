#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105,mod=1e9+7;

int n,k,d,f[maxn][2];

void add(int &x,int v) {x=(x+v)%mod;}

int main() {
	n=Get_Int();
	k=Get_Int();
	d=Get_Int();
	f[0][0]=1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=min(i,k); j++)
			if(j>=d) {
				add(f[i][1],f[i-j][1]);
				add(f[i][1],f[i-j][0]);
			} else {
				add(f[i][1],f[i-j][1]);
				add(f[i][0],f[i-j][0]);
			}
	printf("%d\n",f[n][1]);
	return 0;;
}