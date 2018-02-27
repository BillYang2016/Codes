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

LL l,r,tot,a[25],f[25][11][11][2];

LL Dp(int Now,int ppre,int pre,bool zero,bool up) {
	if(Now<0)return 1;
	if(!up&&~f[Now][ppre][pre][zero])return f[Now][ppre][pre][zero];
	LL limit=up?a[Now]:9,sum=0;
	for(int i=0; i<=limit; i++) {
		if(!zero&&(i==ppre||i==pre))continue;
		bool zzero=zero&&i==0;
		sum+=Dp(Now-1,zzero?10:pre,zzero?10:i,zzero,up&&i==limit);
	}
	if(!up)f[Now][ppre][pre][zero]=sum;
	return sum;
}

LL Solve(LL x) {
	int tot=0;
	while(x) {
		a[tot++]=x%10;
		x/=10;
	}
	return Dp(tot-1,10,10,1,1);
}

int main() {
	memset(f,-1,sizeof(f));
	l=Get_Int();
	r=Get_Int();
	printf("%lld\n",Solve(r)-Solve(l-1));
	return 0;
} 
