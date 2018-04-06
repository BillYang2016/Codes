#include<bits/stdc++.h>

using namespace std;

typedef unsigned int LL;

inline LL Get_Int() {
	LL num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005,K=31;

struct Linear_Bases {
	vector<LL> a;
	LL b[K+1];
	Linear_Bases() {fill(b,b+K+1,0);}
	void add(LL num) {
		for(int j=K; j>=0; j--)
			if(num>>j&1) {
				if(b[j]) {num^=b[j];continue;}
				b[j]=num;
				for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
				for(int k=j+1; k<=K; k++)if(b[k]>>j&1)b[k]^=b[j];
				break;
			}
	}
	void split() {for(int i=K; i>=0; i--)if(b[i])a.push_back(b[i]);}
	void merge(const Linear_Bases& b) {for(int i=0; i<=K; i++)if(b.b[i])add(b.b[i]);}
	LL cal() {
		LL ans=0;
		for(int i=0; i<=K; i++)ans^=b[i];
		return ans;
	}
} null;

int n,q;
LL a[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right;
		Linear_Bases lb;
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index].left=Left,tree[index].right=Right;
		if(Left==Right) {tree[index].lb.add(a[Left]);return;}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].lb=tree[ls].lb;
		tree[index].lb.merge(tree[rs].lb);
	}
	void modify(int index,int tar,LL val) {
		if(tar<tree[index].left||tar>tree[index].right)return;
		if(tree[index].left==tree[index].right) {
			tree[index].lb=null;
			tree[index].lb.add(val);
			return;
		}
		modify(ls,tar,val);
		modify(rs,tar,val);
		push_up(index);
	}
	Linear_Bases query(int index,int Left,int Right) {
		if(Right<tree[index].left||Left>tree[index].right)return null;
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].lb;
		Linear_Bases l=query(ls,Left,Right),r=query(rs,Left,Right);
		l.merge(r);
		return l;
	}
} st;

void Query(int Left,int Right) {
	Linear_Bases lb=st.query(1,Left,Right);
	lb.split();
	int len=lb.a.size();
	long long Max=lb.cal(),ans=0;
	for(int i=1; i<lb.a.size(); i++)ans+=lb.a[i]^Max;
	printf("%lld\n",ans+Max*((Right-Left+1)-len+1));
}

int main() {
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n);
	while(q--) {
		LL opt=Get_Int(),x=Get_Int(),y=Get_Int();
		if(opt==1)st.modify(1,x,y);
		else Query(x,y);
	}
	return 0;
}