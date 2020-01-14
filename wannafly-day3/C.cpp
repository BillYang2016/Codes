#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,m,a[20][20],Disable[1<<17],f[1<<17];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		a[x][y]=a[y][x]=1;
	}
	for(int S=1; S<(1<<n); S++)
		for(int i=1; i<=n; i++)
			if(S>>(i-1)&1)
				for(int j=i+1; j<=n; j++)
					if((S>>(j-1)&1)&&a[i][j])Disable[S]=1;
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(int S=1; S<(1<<n); S++)
		for(int T=S; T; T=S&(T-1))
			if(!Disable[T])f[S]=min(f[S],f[S^T]+1);
	printf("%d\n",f[(1<<n)-1]-1);
	return 0;
}