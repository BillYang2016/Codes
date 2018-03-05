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

const int maxn=200005,maxm=200005,K=17;

struct President_Tree {
	struct Tree {
		int ls,rs,sum;
	} tree[maxn*20];
	int size;
#define mid ((left+right)>>1)
	int insert(int pre,int left,int right,int val) {
		int now=++size;
		tree[now]=tree[pre];
		tree[now].sum++;
		if(left==right)return now;
		if(val<=mid)tree[now].ls=insert(tree[pre].ls,left,mid,val);
		else tree[now].rs=insert(tree[pre].rs,mid+1,right,val);
		return now;
	}
	bool query(int left,int right,int lt,int rt,int Left,int Right) {
		if(Right<left||Left>right||(!lt&&!rt))return 0;
		if(Left<=left&&Right>=right)return tree[rt].sum-tree[lt].sum>0;
		return query(left,mid,tree[lt].ls,tree[rt].ls,Left,Right)|query(mid+1,right,tree[lt].rs,tree[rt].rs,Left,Right);
	}
} pt;

int n,m,root[maxn],a;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int();
		root[i]=pt.insert(root[i-1],0,maxm,x);
	}
	for(int i=1; i<=m; i++) {
		int b=Get_Int(),x=Get_Int(),l=Get_Int(),r=Get_Int();
		a=0;
		for(int j=K; j>=0; j--) {
			if(!(b&(1<<j)))a^=1<<j;
			int left=max(a-x,0),right=(a|((1<<j)-1))-x;
			if(right<left||!pt.query(0,maxm,root[l-1],root[r],left,right))a^=1<<j;
		}
		printf("%d\n",a^b);
	}
	return 0;
}