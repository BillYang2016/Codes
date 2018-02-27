#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;
#define pii pair<LL,LL>
#define mp make_pair

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

LL x,y,k;
int high[25],low[25];
bool vst[25][1005][165];
pii f[25][1005][165];

pii Dp(int Now,int last,int sum,bool down,bool up) {
	if(Now<0) {
		if(last+sum>=k)return mp(1,0);
		else return mp(0,last+sum);
	}
	if(!down&&!up&&vst[Now][last][sum])return f[Now][last][sum];
	int lowbit=down?low[Now]:0,highbit=up?high[Now]:9;
	pii ans=mp(0,last);
	for(int i=lowbit; i<=highbit; i++) {
		pii tmp=Dp(Now-1,ans.second,sum+i,down&&i==lowbit,up&&i==highbit);
		ans.first+=tmp.first;
		ans.second=tmp.second;
	}
	if(!down&&!up) {
		vst[Now][last][sum]=1;
		f[Now][last][sum]=ans;
	}
	return ans;
}

int main() {
	x=Get_Int();
	y=Get_Int();
	k=Get_Int();
	int cntlow=0,cnthigh=0;
	while(x) {
		low[cntlow++]=x%10;
		x/=10;
	}
	while(y) {
		high[cnthigh++]=y%10;
		y/=10;
	}
	printf("%lld\n",Dp(cnthigh-1,0,0,1,1).first);
	return 0;
}