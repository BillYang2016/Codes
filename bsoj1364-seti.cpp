#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=75;

int n,p,a[maxn][maxn];

int Quick_Pow(int a,int b) {
	int ans=1;
	for(; b; b>>=1,a=a*a%p)if(b&1)ans=ans*a%p;
	return ans;
}

void Gauss_Jordan(int n) {
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(a[row][i])break;
		if(row>n)continue;
		if(row!=i)for(int j=1; j<=n+1; j++)swap(a[i][j],a[row][j]);
		int t=Quick_Pow(a[i][i],p-2);
		for(int j=1; j<=n+1; j++)a[i][j]=a[i][j]*t%p;
		for(int j=1; j<=n; j++)if(j!=i) {
			t=a[j][i];
			for(int k=1; k<=n+1; k++)a[j][k]=(a[j][k]-t*a[i][k]%p+p)%p;
		}
	}
}

char s[maxn];

int main() {
	p=Get_Int();
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1; i<=n; i++) {
		int sum=1;
		for(int j=1; j<=n; j++) {
			a[i][j]=sum;
			sum=sum*i%p;
		}
		a[i][n+1]=isalpha(s[i])?s[i]-'a'+1:0;
	}
	Gauss_Jordan(n);
	for(int i=1; i<=n; i++)printf("%d ",a[i][n+1]);
	return 0;
}