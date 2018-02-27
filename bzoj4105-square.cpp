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

const int maxn=100005,maxp=10005;

int a[maxn],Next[maxp];
bool inCircle[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right,sum,lazy;
		bool inCircle;
		int pos,len,circle[65];
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index].left=Left,tree[index].right=Right;
		if(Left==Right) {
			tree[index].sum=a[Left];
			build_circle(index,a[Left]);
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void build_circle(int index,int val) {
		tree[index].inCircle=inCircle[val];
		if(tree[index].inCircle) {
			tree[index].pos=0;for(int now=val; !tree[index].len||now!=val; now=Next[now])tree[index].circle[tree[index].len++]=now;
		}
	}
	void push_up(int index) {
		tree[index].sum=tree[ls].sum+tree[rs].sum;
		tree[index].inCircle=tree[ls].inCircle&&tree[rs].inCircle;
		if(tree[index].inCircle) {
			tree[index].len=tree[ls].len/__gcd(tree[ls].len,tree[rs].len)*tree[rs].len;
			tree[index].pos=0;
			int lpos=tree[ls].pos,rpos=tree[rs].pos;
			for(int i=0; i<tree[index].len; i++) {
				tree[index].circle[i]=tree[ls].circle[lpos++]+tree[rs].circle[rpos++];
				if(lpos==tree[ls].len)lpos=0;
				if(rpos==tree[rs].len)rpos=0;
			}
		}
	}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		tree[ls].lazy+=tree[index].lazy,tree[rs].lazy+=tree[index].lazy;
		tree[ls].pos=(tree[ls].pos+tree[index].lazy)%tree[ls].len,tree[rs].pos=(tree[rs].pos+tree[index].lazy)%tree[rs].len;
		tree[ls].sum=tree[ls].circle[tree[ls].pos],tree[rs].sum=tree[rs].circle[tree[rs].pos];
		tree[index].lazy=0;
	}
	void modify(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right&&tree[index].inCircle) {
			tree[index].lazy++;
			tree[index].pos++;
			if(tree[index].pos==tree[index].len)tree[index].pos=0;
			tree[index].sum=tree[index].circle[tree[index].pos];
			return;
		}
		if(tree[index].left==tree[index].right) { //叶子结点
			tree[index].sum=Next[tree[index].sum];
			build_circle(index,tree[index].sum);
			return;
		}
		push_down(index);
		modify(ls,Left,Right);
		modify(rs,Left,Right);
		push_up(index);
	}
	int query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].sum;
		push_down(index);
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

int n,m,p;
bool vst[maxp];

int main() {
	n=Get_Int();
	m=Get_Int();
	p=Get_Int();
	for(int i=0; i<p; i++) {
		Next[i]=i*i%p;
		inCircle[i]=1;
	}
	for(int i=0; i<p; i++)
		if(!vst[i]) {
			int now=i;
			while(!vst[now]) {
				vst[now]=1;
				now=Next[now];
			}
			for(int j=i; j!=now; j=Next[j])inCircle[j]=0;
		}
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n);
	for(int i=1; i<=m; i++) {
		int opt=Get_Int(),l=Get_Int(),r=Get_Int();
		if(opt==0)st.modify(1,l,r);
		else printf("%d\n",st.query(1,l,r));
	}
	return 0;
}
