#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=2005,base1=123,base2=10007; 

int n,m,a[maxn][maxn],ans=0;
unsigned int LU[maxn][maxn],RU[maxn][maxn],LD[maxn][maxn],Pow1[maxn],Pow2[maxn];

bool Check(int x1,int y1,int x2,int y2) {
	int h1=LU[x2][y2]-LU[x2][y1-1]*Pow2[y2-y1+1]-LU[x1-1][y2]*Pow1[x2-x1+1]+LU[x1-1][y1-1]*Pow2[y2-y1+1]*Pow1[x2-x1+1];
	int h2=RU[x2][y1]-RU[x2][y2+1]*Pow2[y2-y1+1]-RU[x1-1][y1]*Pow1[x2-x1+1]+RU[x1-1][y2+1]*Pow2[y2-y1+1]*Pow1[x2-x1+1];
	if(h1!=h2)return false;
	int h3=LD[x1][y2]-LD[x1][y1-1]*Pow2[y2-y1+1]-LD[x2+1][y2]*Pow1[x2-x1+1]+LD[x2+1][y1-1]*Pow2[y2-y1+1]*Pow1[x2-x1+1];
	return h2==h3;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			a[(i<<1)-1][(j<<1)-1]=Get_Int();
	n=(n<<1)-1,m=(m<<1)-1;
	Pow1[0]=Pow2[0]=1;
	for(int i=1; i<=n; i++)Pow1[i]=Pow1[i-1]*base1;
	for(int i=1; i<=m; i++)Pow2[i]=Pow2[i-1]*base2;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)LU[i][j]=LU[i][j-1]*base2+a[i][j];
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)LU[i][j]+=LU[i-1][j]*base1;
	for(int i=1; i<=n; i++)
		for(int j=m; j>=1; j--)RU[i][j]=RU[i][j+1]*base2+a[i][j];
	for(int i=1; i<=n; i++)
		for(int j=m; j>=1; j--)RU[i][j]+=RU[i-1][j]*base1;
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)LD[i][j]=LD[i][j-1]*base2+a[i][j];
	for(int i=n; i>=1; i--)
		for(int j=1; j<=m; j++)LD[i][j]+=LD[i+1][j]*base1;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++)
			if(!((i+j)&1)) {
				int Left=1,Right=min({i,j,n-i+1,m-j+1});
				while(Left<=Right) {
					int mid=(Left+Right)>>1;
					if(Check(i-mid+1,j-mid+1,i+mid-1,j+mid-1))Left=mid+1;
					else Right=mid-1;
				}
				ans+=(Right+(i&1))>>1;
			}
	printf("%d\n",ans);
	return 0;
}