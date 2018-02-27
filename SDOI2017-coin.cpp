#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>

using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

void Get_Next(string s,int n) {
	fail[1]=0;
	for(int i=2; i<=n; i++) {
		for(int t=fail[i-1]; t&&s[t+1]!=s[i]; t=fail[t]);
		fail[i]=s[i]==s[t+1]?t+1:0;
	}
}

double Cal(string a,string b) {
	int n=m<<1;
	string s=' '+a+b;
	Get_Next(s,n);
	double ans=0;
	for(int now=fail[n]; now; now=fail[now])if(now<m)ans+=div[m-now];
	return ans;
}

void build() {
	div[0]=1;
	for(int i=1; i<=m; i++)div[i]=div[i-1]/2;
	for(int i=1; i<=n; i++)a[n+1][i]=1;a[n+1][n+2]=1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++)a[i][j]=Cal(s[i],s[j]);
		a[i][n+1]=-div[m];
	}
}

void Gauss_Jordan(int n) {
	for(int i=1; i<=n; i++) {
		int row=i;
		for(; row<=n; row++)if(fabs(a[row][i])>eps)break;
		if(row>n)continue;
		if(row!=i)for(int j=1; j<=n+1; j++)swap(a[i][j],a[row][j]);
		double t=a[i][i];
		for(int j=1; j<=n+1; j++)a[i][j]/=t;
		for(int j=1; j<=n; j++)
			if(j!=i) {
				t=a[j][i];
				for(int k=1; k<=n+1; k++)a[j][k]-=t*a[i][k];
			}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)scanf("%s",s[i]);
	build();
	Gauss_Jordan(n+1);
	for(int i=1; i<=n; i++)printf("%0.10lf\n",a[i][n+2]);
	return 0;
}