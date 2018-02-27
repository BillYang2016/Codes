#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;
#define mp make_pair
#define pii pair<LL,bitset<65> >

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

const int maxn=100005;
const LL mod=19961993;

int Prime[65];

struct Tree {
	int left,right;
	LL val;
	bitset<65>vst;
	Tree(int l=0,int r=0,LL v=1):left(l),right(r),val(v),vst(bitset<65>()) {}
};

struct Segment_Tree {
	Tree tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right) {
			tree[index].val=3;
			tree[index].vst[2]=1;
			return;
		}
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
		push_up(index);
	}
	void push_up(int index) {
		tree[index].val=tree[ls].val*tree[rs].val%mod;
		tree[index].vst=tree[ls].vst|tree[rs].vst;
	}
	void modify(int index,int target,LL val) {
		if(target>tree[index].right||target<tree[index].left)return;
		if(tree[index].left==tree[index].right) {
			tree[index].val=val;
			tree[index].vst.reset();
			for(int i=1; i<=60; i++)tree[index].vst[i]=val%Prime[i]==0;
			return;
		}
		modify(ls,target,val);
		modify(rs,target,val);
		push_up(index);
	}
	pii query(int index,int Left,int Right) {
		if(Left>tree[index].right||Right<tree[index].left)return mp(1,bitset<65>());
		if(Left<=tree[index].left&&Right>=tree[index].right)return mp(tree[index].val,tree[index].vst);
		pii l=query(ls,Left,Right),r=query(rs,Left,Right);
		return mp(l.first*r.first%mod,l.second|r.second);
	}
} st;

bool vst[305];
int cnt=0;
LL val[65];

LL Quick_Pow(LL a,LL b) {
	LL ans=1;
	while(b) {
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

void Table(int n) {
	for(int i=2; i<=n; i++) {
		if(!vst[i])Prime[++cnt]=i;
		for(int j=1; j<=cnt&&i*Prime[j]<=n; j++) {
			vst[i*Prime[j]]=1;
			if(i%Prime[j]==0)break;
		}
	}
	for(int i=1; i<=60; i++)val[i]=(Prime[i]-1)*Quick_Pow(Prime[i],mod-2)%mod;
}

int n=100000,q;

int main() {
	Table(281);
	q=Get_Int();
	st.build(1,1,n);
	while(q--) {
		int opt=Get_Int();
		LL x=Get_Int(),y=Get_Int();
		if(opt==0) {
			pii sum=st.query(1,x,y);
			LL ans=sum.first;
			for(int i=1; i<=60; i++)
				if(sum.second[i])ans=ans*val[i]%mod;
			printf("%lld\n",ans);
		} else st.modify(1,x,y);
	}
	return 0;
} 
