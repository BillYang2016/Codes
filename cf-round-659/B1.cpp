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

int n,k,l,d[maxn],f[maxn][maxn<<1];

bool Check(int x,int t) {
	if(t<=k)return l>=d[x]+t;
	else return l>=d[x]+2*k-t;
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		k=Get_Int();
		l=Get_Int();
		for(int i=1; i<=n; i++)d[i]=Get_Int();
		memset(f,0,sizeof(f));
		for(int i=0; i<2*k; i++)f[0][i]=1;
		for(int i=1; i<=n; i++)
			for(int j=0; j<2*k; j++) {
				int last=j-1;
				if(last==-1)last+=2*k;
				if(Check(i,j))f[i][j]=f[i-1][last]||f[i][last];
			}
		bool flag=0;
		for(int i=0; i<2*k; i++)if(f[n][i]) {flag=1;break;}
		puts(flag?"Yes":"No");
	}
	return 0;
}