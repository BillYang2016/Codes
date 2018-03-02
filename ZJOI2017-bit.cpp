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

const int maxn=100005,mod=998244353;

LL ans;

LL Quick_Pow(LL a,LL b) {
	LL sum=1;
	for(; b; b>>=1,a=a*a%mod)if(b&1)sum=sum*a%mod;
	return sum;
}

LL merge(LL x,LL y) {
	return (x*y%mod+(mod+1-x)%mod*(mod+1-y)%mod)%mod;
}

struct Segment_Tree_in {
	struct Tree {
		int lson,rson;
		LL p;
		Tree() {lson=rson=0,p=1;}
	} tree[maxn*200];
	int size;
#define ls tree[index].lson
#define rs tree[index].rson
#define mid ((left+right)>>1)
	void modify(int &index,int left,int right,int Left,int Right,LL v) {
		if(Right<left||Left>right)return;
		if(!index)index=++size;
		if(Left<=left&&Right>=right) {
			tree[index].p=merge(tree[index].p,v);
			return;
		}
		modify(ls,left,mid,Left,Right,v);
		modify(rs,mid+1,right,Left,Right,v);
	}
	void query(int index,int left,int right,int pos) {
		if(!index||pos<left||pos>right)return;
		ans=merge(ans,tree[index].p);
		if(left==right)return;
		query(ls,left,mid,pos);
		query(rs,mid+1,right,pos);
	}
} stin;

#undef ls
#undef rs

int n,m;

struct Segment_Tree {
	int root[maxn<<2];
#define ls index<<1
#define rs index<<1|1
#define mid ((left+right)>>1)
	void modify(int index,int left,int right,int Left,int Right,int L2,int R2,LL v) {
		if(Right<left||Left>right)return;
		if(Left<=left&&Right>=right) {
			stin.modify(root[index],0,n+1,L2,R2,v);
			return;
		}
		modify(ls,left,mid,Left,Right,L2,R2,v);
		modify(rs,mid+1,right,Left,Right,L2,R2,v);
	}
	void query(int index,int left,int right,int pos1,int pos2) {
		if(pos1<left||pos1>right)return;
		if(root[index])stin.query(root[index],0,n+1,pos2);
		if(left==right)return;
		query(ls,left,mid,pos1,pos2);
		query(rs,mid+1,right,pos1,pos2);
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int opt=Get_Int(),x=Get_Int(),y=Get_Int();
		if(opt==1) {
			LL p=Quick_Pow(y-x+1,mod-2);
			if(x>1)st.modify(1,0,n,1,x-1,x,y,(mod+1-p)%mod);
			if(y<n)st.modify(1,0,n,x,y,y+1,n,(mod+1-p)%mod);
			LL p2=p*2%mod;
			st.modify(1,0,n,x,y,x,y,(mod+1-p2)%mod);
			st.modify(1,0,n,0,0,0,x-1,0);
			st.modify(1,0,n,0,0,y+1,n+1,0);
			st.modify(1,0,n,0,0,x,y,p);
		} else {
			ans=1;
			st.query(1,0,n,x-1,y);
			printf("%lld\n",ans);
		}
	}
	return 0;
}