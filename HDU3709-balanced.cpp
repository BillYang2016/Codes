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

int a[25];
LL f[25][1505][25];

LL Dp(int Now,int s,int p,bool up) {
	if(Now<0)return s==0;
	if(s<0)return 0;
	if(!up&&~f[Now][s][p])return f[Now][s][p];
	int Limit=up?a[Now]:9;
	LL sum=0;
	for(int i=0; i<=Limit; i++)sum+=Dp(Now-1,s+(Now-p)*i,p,up&&i==Limit);
	if(!up)f[Now][s][p]=sum;
	return sum;
}

LL Cal(LL x) {
	if(x<0)return 0; 
	int tot=0;
	while(x) {
		a[tot++]=x%10;
		x/=10;
	}
	LL sum=0;
	for(int i=0; i<tot; i++)sum+=Dp(tot-1,0,i,1);
	return sum-tot+1;
}

int main() {
	memset(f,-1,sizeof(f));
	int t=Get_Int();
	while(t--) {
		LL x=Get_Int(),y=Get_Int();
		printf("%lld\n",Cal(y)-Cal(x-1));
	}
	return 0;
}