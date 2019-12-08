#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,w,a[405],b[405],t[405],f[405][405];

int main() {
	n=Get_Int();
	w=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		b[i]=Get_Int();
		t[i]=ceil(double(Get_Int())/w);
	}
	for(int len=1; len<=n; len++) {
		for(int i=1; i+len-1<=n; i++) {
			int j=i+len-1;
			f[i][j]=INT_MAX/2;
			for(int k=i; k<=j; k++) {
				int l_cost=k-1>=i?f[i][k-1]:0;
				int r_cost=k+1<=j?f[k+1][j]:0;
				f[i][j]=min(f[i][j],l_cost+r_cost+t[k]*(a[k]+b[i-1]+b[j+1]));
			}
		}
	}
	printf("%d\n",f[1][n]);
	return 0;
}
