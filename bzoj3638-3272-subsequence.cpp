#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Tag {
	int lmax,rmax,max,sum;
	int lp,rp,p1,p2;
	Tag(int p=0,int v=0) {
		lp=rp=p1=p2=p;
		lmax=rmax=max=sum=v;
	}
	bool check() const {return lmax==0&&rmax==0&&max==0&&sum==0&&lp==0&&rp==0&&p1==0&&p2==0;}
	Tag operator + (const Tag &b) {
		if(check())return b;
		if(b.check())return *this;
		Tag ans;
		ans.sum=sum+b.sum;
		ans.lmax=lmax,ans.lp=lp;
		if(sum+b.lmax>ans.lmax)ans.lmax=sum+b.lmax,ans.lp=b.lp;
		ans.rmax=b.rmax,ans.rp=b.rp;
		if(b.sum+rmax>ans.rmax)ans.rmax=b.sum+rmax,ans.rp=rp;
		ans.max=rmax+b.lmax,ans.p1=rp,ans.p2=b.lp;
		if(ans.max<max)ans.max=max,ans.p1=p1,ans.p2=p2;
		if(ans.max<b.max)ans.max=b.max,ans.p1=b.p1,ans.p2=b.p2;
		return ans;
	}
};

int n,q,a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		bool rev;
		Tag max,min;
		Tree(int l=0,int r=0,int v=0):left(l),right(r),max(Tag(l,v)),min(Tag(l,-v)) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {tree[index]=Tree(Left,Right,a[Left]);return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].max=tree[ls].max+tree[rs].max;
		tree[index].min=tree[ls].min+tree[rs].min;
	}
	void reverse(int index) {
		swap(tree[index].min,tree[index].max);
		tree[index].rev^=1;
	}
	void push_down(int index) {
		if(tree[index].left==tree[index].right||!tree[index].rev)return;
		reverse(ls);
		reverse(rs);
		tree[index].rev=0;
	}
	void reverse(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {reverse(index);return;}
		push_down(index);
		reverse(ls,Left,Right);
		reverse(rs,Left,Right);
		push_up(index);
	}
	void modify(int index,int tar,int val) {
		if(tar<tree[index].left||tar>tree[index].right)return;
		if(tree[index].left==tree[index].right) {tree[index]=Tree(tree[index].left,tree[index].right,val);return;}
		push_down(index);
		modify(ls,tar,val);
		modify(rs,tar,val);
		push_up(index);
	}
	Tag query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return 0;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].max;
		push_down(index);
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

#define pii pair<int,int>

int Query(int Left,int Right,int k) {
	vector<pii> reved;
	int ans=0;
	while(k--) {
		Tag tmp=st.query(1,Left,Right);
		if(tmp.max>0)ans+=tmp.max;
		else break;
		st.reverse(1,tmp.p1,tmp.p2);
		reved.push_back(pii(tmp.p1,tmp.p2));
	}
	for(pii x:reved)st.reverse(1,x.first,x.second);
	return ans;
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n);
	q=Get_Int();
	while(q--) {
		int opt=Get_Int(),l=Get_Int(),r=Get_Int();
		if(opt==1)printf("%d\n",Query(l,r,Get_Int()));
		else st.modify(1,l,r);
	}
	return 0;
}