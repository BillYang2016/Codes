#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define mp make_pair
#define pii pair<LL,int>

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

LL n,m,a[maxn],ans[maxn]; 

bool Check(LL x) {
	LL sum=m;
	for(int i=1; i<=n; i++) {
		sum-=x/a[i];
		if(sum<0)return 0;
	}
	return 1;
}

int main() {
	m=Get_Int();
	n=Get_Int();
	LL Left=0,Right=0;
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		Right=max(Right,a[i]);
	}
	Left=Right+1,Right*=m;
	while(Left<=Right) {
		LL mid=(Left+Right)>>1;
		if(Check(mid))Left=mid+1;
		else Right=mid-1;
	}
	LL x=Right,sum=0;
	for(int i=1; i<=n; i++)Right=min(Right,max((x/a[i]-1)*a[i],0ll));
	priority_queue<pii,vector<pii>,greater<pii> > Q;
	for(int i=1; i<=n; i++)sum+=Right/a[i],Q.push(mp(Right/a[i]*a[i],i));
	while(sum<m) {
		pii Now=Q.top();
		Q.pop();
		ans[Now.second]=++sum;
		Now.first+=a[Now.second];
		Q.push(Now);
	}
	for(int i=1; i<=n; i++)printf("%lld%c",ans[i],i==n?'\n':' ');
	return 0;
}