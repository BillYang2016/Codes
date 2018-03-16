#include<bits/stdc++.h>

using namespace std;

typedef long long LL; 

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

int K,cnt=0,a[65];
LL L,R,f[65][4005][2];

LL Dp1(int Now,LL sum,bool up) {
	if(!Now)return sum;
	if(~f[Now][sum][up])return f[Now][sum][up];
	LL &now=f[Now][sum][up],lim=up?a[Now]:K-1;
	now=0;
	for(int i=0; i<=lim; i++)now+=Dp1(Now-1,sum+i*(Now-1),up&&(i==lim));
	return now;
}

LL Dp2(int Now,LL sum,int pos,LL up) {
	if(sum<0)return 0;
	if(!Now)return sum;
	if(~f[Now][sum][up])return f[Now][sum][up];
	LL &now=f[Now][sum][up],lim=up?a[Now]:K-1;
	now=0;
	for(int i=0; i<=lim; i++) {
		if(Now>=pos)now+=Dp2(Now-1,sum+i,pos,up&&(i==lim));
		else now+=Dp2(Now-1,sum-i,pos,up&&(i==lim));
	}
	return now;
}

LL Solve(LL x) {
	int cnt=0;
	memset(f,-1,sizeof(f));
	while(x) {
		a[++cnt]=x%K;
		x/=K;
	}
	LL ans=Dp1(cnt,0,1);
	for(int i=2; i<=cnt; i++) {
		memset(f,-1,sizeof(f));
		ans-=Dp2(cnt,0,i,1);
	}
	return ans;
}

int main() {
	L=Get_Int();
	R=Get_Int();
	K=Get_Int();
	printf("%lld\n",Solve(R)-Solve(L-1));
	return 0;
}