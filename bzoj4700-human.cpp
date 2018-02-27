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

inline const int Get_Int() {
	int num=0,bj=1;
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

LL n,ATK,ans=LLONG_MAX;

struct Human {
	LL a,b,c;
	int id;
	bool operator < (const Human& x) const {
		return x.a*b<a*x.b;
	}
} p[maxn];

bool cmpk(const Human& x,const Human& y) {
	return x.a<y.a;
}

bool cmpxy(const Human& x,const Human& y) {
	return x.b<y.b||(x.b==y.b&&x.c<y.c);
}

double Solve(int x,int y) {
	return (p[x].c-p[y].c)/(p[x].b-p[y].b);
}

void CDQBinary(int Left,int Right) {
	if(Left==Right)return;
	int mid=(Left+Right)>>1,lpos=Left,rpos=mid+1;
	for(int i=Left; i<=Right; i++)
		if(p[i].id<=mid)tmp[lpos++]=p[i];
		else tmp[rpos++]=p[i];
	for(int i=Left; i<=Right; i++)p[i]=tmp[i];
	CDQBinary(Left,mid);
	deque<int>Q;
	for(int Left; i<=mid; i++) {
		while(Q.size()>=2&&Slope(Q[Q.size()-2],Q.back())>Slope(Q.back(),i))Q.pop_back();
		Q.push_back(i);
	}
	for(int i=mid+1; i<=Right; i++) {
		while(Q.size()>=2&&Slope(Q.front(),Q[1])<p[i].k)Q.pop_front();
		ans=min(ans,p[i].c+p[Q.front()].c-p[i].a*p[Q.front()].b);
	}
	CDQBinary(mid+1,Right);
	merge(p+Left,p+mid+1,p+mid+1,p+Right+1,tmp,cmpxy);
	int tot=0;
	for(int i=Left; i<=Right; i++)p[i]=tmp[tot++];
}

int main() {
	n=Get_Int();
	ATK=Get_Int();
	for(int i=1; i<=n; i++) {
		p[i].a=Get_Int();
		p[i].b=ceil(double(Get_Int())/ATK)-1;
	}
	sort(p+1,p+n+1);
	for(int i=1; i<=n; i++) {
		sumv[i]=sumv[i-1]+p[i].v;
		sumt[i]=sumt[i-1]+p[i].b;
	}
	for(int i=1; i<=n; i++) {
		p[i].c=(sumv[n]-sumv[i])*p[i].b+sumt[i]*p[i].a;
		p[i].id=i;
	}
	sort(p+1,p+n+1,cmpk);
	CDQBinary(1,n);
	printf("%lld\n",ans);
	return 0;
}
