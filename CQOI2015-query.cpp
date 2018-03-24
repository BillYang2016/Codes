#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
#define pii pair<int,int>
mt19937 g(rand());

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Treap {
	struct Tree {
		int l,r,size;
		int val;
		LL sum;
		Tree(int s=0,int v=0):size(s),val(v),sum(v) {l=r=0;}
	} tree[maxn*110];
	int size;
#define ls tree[now].l
#define rs tree[now].r
	int newnode(int v) {tree[++size]=Tree(1,v);return size;}
	void push_up(int now) {
		tree[now].size=tree[ls].size+tree[rs].size+1;
		tree[now].sum=tree[ls].sum+tree[rs].sum+tree[now].val;
	}
	pii split(int index,int num) {
		if(!index)return pii(0,0);
		int now=++size;
		tree[now]=tree[index];
		if(num<=tree[ls].size) {
			pii lt=split(ls,num);
			ls=lt.second;
			push_up(now);
			return pii(lt.first,now);
		} else {
			pii rt=split(rs,num-tree[ls].size-1);
			rs=rt.first;
			push_up(now);
			return pii(now,rt.second);
		}
	}
	int merge(int a,int b) {
		if(!a||!b)return a+b;
		int now=++size;
		if(g()%(tree[a].size+tree[b].size)<tree[a].size) {
			tree[now]=tree[a];
			rs=merge(rs,b);
		} else {
			tree[now]=tree[b];
			ls=merge(a,ls);
		}
		push_up(now);
		return now;
	}
	int get_rank(int now,int v) {
		if(!now)return 0;
		if(v<tree[now].val)return get_rank(ls,v);
		else return tree[ls].size+1+get_rank(rs,v);
	}
	int insert(int now,int v) {
		int k=get_rank(now,v);
		pii tmp=split(now,k);
		return merge(merge(tmp.first,newnode(v)),tmp.second);
	}
	int remove(int now,int v) {
		int k=get_rank(now,v);
		return merge(split(now,k-1).first,split(now,k).second);
	}
	LL query(int now,int k) {
		if(!now||!k)return 0;
		if(k<=tree[ls].size)return query(ls,k);
		return tree[ls].sum+tree[now].val+query(rs,k-tree[ls].size-1);
	}
} treap;

int n,m,root[maxn];
LL ans=1;
vector<pii> a[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		int l=Get_Int(),r=Get_Int(),v=Get_Int();
		a[l].push_back(pii(1,v));
		a[r+1].push_back(pii(-1,v));
	}
	for(int i=1; i<=m; i++) {
		root[i]=root[i-1];
		for(pii tmp:a[i]) {
			int opt=tmp.first,v=tmp.second;
			if(opt==1)root[i]=treap.insert(root[i],v);
			else root[i]=treap.remove(root[i],v);
		}
	}
	while(m--) {
		int x=Get_Int(),a=Get_Int(),b=Get_Int(),c=Get_Int();
		int k=1+(a*ans+b)%c;
		if(k>=treap.tree[root[x]].size)ans=treap.tree[root[x]].sum;
		else ans=treap.query(root[x],k);
		printf("%lld\n",ans);
	}
	return 0;
}