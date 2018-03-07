#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=20005;

int f[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		int min,lazy;
		Tree(int l=0,int r=0):left(l),right(r),min(INT_MAX/2),lazy(0) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].min=f[Left];
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].min=min(tree[ls].min,tree[rs].min);
	}
	void modify(int index,int val) {
		tree[index].min+=val;
		tree[index].lazy+=val;
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		modify(ls,tree[index].lazy);
		modify(rs,tree[index].lazy);
		tree[index].lazy=0;
	}
	void modify(int index,int Left,int Right,int val) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			modify(index,val);
			return;
		}
		push_down(index);
		modify(ls,Left,Right,val);
		modify(rs,Left,Right,val);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return INT_MAX/2;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].min;
		push_down(index);
		return min(query(ls,Left,Right),query(rs,Left,Right));
	}
} sgt;

int n,k,dist[maxn],c[maxn],s[maxn],w[maxn],st[maxn],ed[maxn],ans=0;
vector<int> vec[maxn];

int main() {
	n=Get_Int();
	k=Get_Int();
	for(int i=2; i<=n; i++)dist[i]=Get_Int();
	for(int i=1; i<=n; i++)c[i]=Get_Int();
	for(int i=1; i<=n; i++)s[i]=Get_Int();
	for(int i=1; i<=n; i++)w[i]=Get_Int();
	dist[++n]=INT_MAX/2,w[n]=INT_MAX/2,k++;
	for(int i=1; i<=n; i++) {
		st[i]=lower_bound(dist+1,dist+n+1,dist[i]-s[i])-dist;
		ed[i]=upper_bound(dist+1,dist+n+1,dist[i]+s[i])-dist-1;
		vec[ed[i]].push_back(i);
	}
	int tmp=0;
	for(int i=1; i<=n; i++) { //f(i,1)
		f[i]=tmp+c[i];
		for(int x:vec[i])tmp+=w[x];
	}
	ans=f[n];
	for(int j=2; j<=k; j++) {
		sgt.build(1,1,n);
		for(int i=1; i<=n; i++) {
			f[i]=sgt.query(1,1,i-1)+c[i];
			for(int x:vec[i])sgt.modify(1,1,st[x]-1,w[x]);
		}
		ans=min(ans,f[n]);
	}
	printf("%d\n",ans);
	return 0;
}