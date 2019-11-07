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

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=20005;

int n,m,a[maxn],b[maxn],Hash[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right,val,lazy;
		Tree() {}
		Tree(int l,int r,int v):left(l),right(r),val(v),lazy(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void modify(int index,int val) {tree[index].val=tree[index].lazy=val;}
	void push_up(int index) {
		if(tree[ls].val==tree[rs].val)tree[index].val=tree[ls].val;
		else tree[index].val=-1;
	}
	void push_down(int index) {
		int &lazy=tree[index].lazy;
		if(!lazy)return;
		modify(ls,lazy);
		modify(rs,lazy);
		lazy=0;
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right,0);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void modify(int index,int Left,int Right,int val) {
		if(Left<=tree[index].left&&Right>=tree[index].right) {modify(index,val);return;}
		push_down(index);
		if(Left<=tree[ls].right)modify(ls,Left,Right,val);
		if(Right>=tree[rs].left)modify(rs,Left,Right,val);
		push_up(index);
	}
	void query(int index) {
		if(tree[index].val!=-1) {Hash[tree[index].val]=1;return;}
		push_down(index);
		query(ls);
		query(rs);
	}
} st;

void Discretization(int n) {
	memcpy(b,a,sizeof(b));
	sort(a+1,a+n+1);
	int cnt=unique(a+1,a+n+1)-a-1;
	for(int i=1; i<=n; i++)b[i]=lower_bound(a+1,a+cnt+1,b[i])-a;
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		for(int i=1; i<=n; i++)Hash[i]=0;
		st.build(1,1,n<<1);
		for(int i=1; i<=n; i++)a[(i<<1)-1]=Get_Int(),a[i<<1]=Get_Int();
		Discretization(n<<1);
		for(int i=1; i<=n; i++)st.modify(1,b[(i<<1)-1],b[i<<1],i);
		st.query(1);
		int ans=0;
		for(int i=1; i<=n; i++)if(Hash[i])ans++;
		printf("%d\n",ans);
	}
	return 0;
}