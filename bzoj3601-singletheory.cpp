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

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxd=105,maxw=1005;

LL a[maxd][maxd],ans[maxd],p[maxw],up[maxw];

void Simplify(int n,int x) {
	if(!a[x][x]) { //选主元
		for(int i=x+1; i<=n; i++)
			if(a[i][x]) {
				for(int j=1; j<=n+1; j++)swap(a[i][j],a[x][j]);
				break;
			}
	}
	LL tmp=inv(a[x][x]);
	for(int i=x+1; i<=n; i++) {
		if(!a[i][x])continue;
		LL mul=a[i][x]*tmp%mod;
		for(int j=x; j<=n+1; j++)a[i][j]=(a[i][j]-a[x][j]*mul%mod+mod)%mod;
	}
}

void Gauss(int n) {
	for(int i=1; i<=n; i++)Simplify(i);
	for(int i=n; i>=1; i--) { //回代
		for(int j=i+1; j<=n; j++)a[i][n+1]=(a[i][n+1]-a[i][j]*ans[j]%mod+mod)%mod;
		ans[i]=a[i][n+1]*inv(a[i][i]);
	}
}

int main() {
	n=Get_Int();
	d=Get_Int();
	w=Get_Int();
	for(int i=1; i<=w; i++) {
		p[i]=Get_Int();
		up[i]=Get_Int();
	}
	LL sum=0;
	for(int i=1; i<=d+1; i++) { //构造方程
		a[i][1]=i;
		for(int j=2; j<=d+1; j++)a[i][j]=a[i][j-1]*i%mod;
		a[i][d+2]=(a[i-1][d+2]+Quick_Pow(i,d))%mod;
	}
	Gauss(d+1);
	LL ans=0;
	for(int i=1; i<=d+1; i++) {
		LL sum=1;
		for(int j=1; j<=w; j++) {
			LL tmp=(Quick_Pow(p[j],up[j]*i)-Quick_Pow(p[j],up[j]*i+d-i)+mod)%mod;
			sum=sum*tmp%mod;
		}
		ans=(ans+ans[i]*sum)%mod;
	}
	printf("%lld\n",ans);
	return 0;
} 
