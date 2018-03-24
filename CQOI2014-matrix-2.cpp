#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int n,m;
bool ans[45][45];
bitset<45> a[45],b[45][45];

void Gauss(int n) {
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(a[row][i])break;
		if(row>n)continue;
		swap(a[i],a[row]);
		for(int j=i+1; j<=n; j++)if(a[j][i])a[j]^=a[i];
	}
	for(int i=n; i>=1; i--) {
		ans[1][i]=a[i][i]?a[i][n+1]:1;
		if(ans[1][i])for(int j=1; j<i; j++)if(a[j][i])a[j].flip(n+1);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++)b[1][i][i]=1;
	for(int i=2; i<=n+1; i++)
		for(int j=1; j<=m; j++)
			b[i][j]=b[i-1][j-1]^b[i-1][j]^b[i-1][j+1]^b[i-2][j];
	for(int i=1; i<=m; i++)a[i]=b[n+1][i];
	Gauss(m);
	for(int i=2; i<=n; i++)
		for(int j=1; j<=m; j++)
			ans[i][j]=ans[i-1][j-1]^ans[i-1][j]^ans[i-1][j+1]^ans[i-2][j];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)printf("%d%c",ans[i][j],j==m?'\n':' ');
	return 0;
}