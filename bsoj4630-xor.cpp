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

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=30005,MAX_BASE=60;

struct Linear_Bases {
	LL b[MAX_BASE+5];
	Linear_Bases() {
		fill(b,b+MAX_BASE+1,0);
	}
	Linear_Bases operator + (LL num) {
		Linear_Bases a=*this;
		for(int j=MAX_BASE; j>=0; j--)
			if(num>>j&1) {
				if(a.b[j]) { //该位存在基
					num^=a.b[j];
					continue;
				}
				a.b[j]=num;
				for(int k=j-1; k>=0; k--)if(a.b[j]>>k&1)a.b[j]^=a.b[k];
				for(int k=j+1; k<=MAX_BASE; k++)if(a.b[k]>>j&1)a.b[k]^=a.b[j];
				break;
			}
		return a;
	}
	void operator += (const LL num) {
		*this=*this+num;
	}
	Linear_Bases operator + (const Linear_Bases& b) {
		Linear_Bases a=*this;
		for(int i=0; i<=MAX_BASE; i++)
			if(b.b[i])a+=b.b[i];
		return a;
	}
	void operator += (const Linear_Bases b) {
		*this=*this+b;
	}
	LL cal() { //最大异或和
		LL ans=0;
		for(int i=0; i<=MAX_BASE; i++)ans^=b[i];
		return ans;
	}
};

struct Segment_Tree {
	struct Tree {
		int left,right;
		Linear_Bases lb;
		Tree(int l=0,int r=0):left(l),right(r),lb(Linear_Bases()) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right,LL* a) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].lb+=a[Left];
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid,a);
		build(rs,mid+1,Right,a);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].lb=Linear_Bases();
		tree[index].lb+=tree[ls].lb;
		tree[index].lb+=tree[rs].lb;
	}
	void modify(int index,int target,LL v) {
		if(tree[index].left>target||tree[index].right<target)return;
		if(tree[index].left==tree[index].right) {
			tree[index].lb=Linear_Bases();
			tree[index].lb+=v;
			return;
		}
		modify(ls,target,v);
		modify(rs,target,v);
		push_up(index);
	}
	Linear_Bases query(int index,int Left,int Right) {
		if(tree[index].left>Right||tree[index].right<Left)return Linear_Bases();
		if(Left<=tree[index].left&&Right>=tree[index].right)return tree[index].lb;
		return query(ls,Left,Right)+query(rs,Left,Right);
	}
} st;

int n,q;
LL a[maxn];

int main() {
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	st.build(1,1,n,a);
	while(q--) {
		int opt=Get_Int(),x=Get_Int();
		LL y=Get_Int();
		if(opt==1)st.modify(1,x,y);
		else {
			Linear_Bases lb=st.query(1,x,y);
			printf("%lld\n",lb.cal());
		}
	}
	return 0;
} 
