#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define mp make_pair

const int maxt=20000005,maxn=100005;

int cnt=0;

struct President_Tree {
	struct Tree {
		int lson,rson,val;
		Tree(int l=0,int r=0,int v=0):lson(l),rson(r),val(v) {}
	} tree[maxt];
	#define ls tree[index].lson
	#define rs tree[index].rson
	#define mid ((Left+Right)>>1)
	void update(int &index,int Left,int Right,int pos,int val) {
		tree[++cnt]=tree[index];
		index=cnt;
		tree[index].val+=val;
		if(Left==Right)return;
		if(pos<=mid)update(ls,Left,mid,pos,val);
		else update(rs,mid+1,Right,pos,val);
	}
	int query(int index,int Left,int Right,int left,int right) {
		if(Left>right||Right<left)return 0;
		if(left<=Left&&right>=Right)return tree[index].val;
		return query(ls,Left,mid,left,right)+query(rs,mid+1,Right,left,right);
	}
} pt;

int n,root[maxn];

int main() {
	map<int,int> last,Max;
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		map<int,int> now;
		int x=Get_Int();
		now[x]=i;
		for(auto p:last)now[p.first&x]=max(now[p.first&x],p.second);
		root[i]=root[i-1];
		for(auto p:now) {
			if(Max.count(p.first))pt.update(root[i],1,n,Max[p.first],-1);
			Max[p.first]=p.second;
			pt.update(root[i],1,n,p.second,1);
		}
		last=now;
	}
	int q=Get_Int(),lastans=0;
	while(q--) {
		int l=(Get_Int()^lastans)%n+1,r=(Get_Int()^lastans)%n+1;
		if(l>r)swap(l,r);
		lastans=pt.query(root[r],1,n,l,r);
		printf("%d\n",lastans);
	}
	return 0;
}