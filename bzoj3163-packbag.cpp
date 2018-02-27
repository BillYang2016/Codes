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

#define pii pair<int,int>
#define mp make_pair

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

const int maxn=1005,maxq=300005,maxm=1005;

struct Thing {
	int cost,value,num;
} a[maxn];

struct Query {
	int x,val,id;
	bool operator < (const Query& b) const {
		return x<b.x;
	}
} Q[maxq];

int n,q,f[maxm],ans[maxq],pos=1;

void trans(const Thing& a) {
	for(int mod=0; mod<a.cost; mod++) {
		deque<pii>Q;
		for(int i=0,index; (index=i*a.cost+mod)<=1000; i++) {
			while(!Q.empty()&&Q.front().first<i-a.num)Q.pop_front();
			while(!Q.empty()&&Q.back().second<=f[index]-i*a.value)Q.pop_back(); //允许自己转移到自己
			Q.push_back(mp(i,f[index]-i*a.value));
			f[index]=Q.front().second+i*a.value;
		}
	}
}

void CDQBinary(int Left,int Right) {
	if(Left==Right) {
		while(pos<=q&&Q[pos].x==Left) {
			ans[Q[pos].id]=f[Q[pos].val];
			pos++;
		}
		return;
	}
	int mid=(Left+Right)>>1,tmp[1005];
	memcpy(tmp,f,sizeof(f));
	for(int i=mid+1; i<=Right; i++)trans(a[i]);
	CDQBinary(Left,mid);
	memcpy(f,tmp,sizeof(tmp));
	for(int i=Left; i<=mid; i++)trans(a[i]);
	CDQBinary(mid+1,Right);
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i].cost=Get_Int();
		a[i].value=Get_Int();
		a[i].num=Get_Int();
	}
	q=Get_Int();
	for(int i=1; i<=q; i++) {
		Q[i].x=Get_Int()+1;
		Q[i].val=Get_Int();
		Q[i].id=i;
	}
	sort(Q+1,Q+q+1);
	CDQBinary(1,n);
	for(int i=1; i<=q; i++)printf("%d\n",ans[i]);
	return 0;
} 
