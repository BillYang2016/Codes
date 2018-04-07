#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005;

mt19937 g(rand());

struct Treap {
	struct Tree {
		int child[2],size;
		int d,val;
	} tree[maxn];
	int size,root;
	queue<int> Q;
#define ls(x) tree[x].child[0]
#define rs(x) tree[x].child[1]
#define size(x) tree[x].size
#define d(x) tree[x].d
#define val(x) tree[x].val
	void push_up(int x) {size(x)=size(ls(x))+size(rs(x))+1;}
	int newnode(int val) {
		int now;
		if(!Q.empty()) {
			now=Q.front();
			Q.pop();
			ls(now)=rs(now)=0;
		} else now=++size;
		val(now)=val;
		d(now)=g()%maxn;
		size(now)=1;
		return now;
	}
	void rotate(int &x,int side) {
		int y=tree[x].child[side^1];
		tree[x].child[side^1]=tree[y].child[side];
		tree[y].child[side]=x;
		push_up(x),push_up(y);
		x=y;
	}
	void insert(int &x,int v) {
		if(!x) {x=newnode(v);return;}
		bool side=v>val(x);
		int &y=tree[x].child[side];
		insert(y,v);
		size(x)++;
		if(d(y)<d(x))rotate(x,side^1);
	}
	int cnt,a[maxn];
	void dfs(int x) {
		if(!x)return;
		dfs(ls(x));
		a[++cnt]=val(x);
		Q.push(x);
		dfs(rs(x));
	}
	int build(int l,int r) {
		if(l>r)return 0;
		int mid=(l+r)>>1,now=newnode(a[mid]);
		ls(now)=build(l,mid-1);
		rs(now)=build(mid+1,r);
		push_up(now);
		return now;
	}
	int rebuild(int x) {
		cnt=0;
		dfs(ls(x));
		dfs(rs(x));
		return build(1,cnt);
	}
	void remove(int val) {
		int now=root,fa;
		bool side;
		while(val(now)!=val) {
			fa=now;
			size(now)--;
			if(val<val(now))now=ls(now),side=0;
			else now=rs(now),side=1;
		}
		int pos=rebuild(now);
		if(now!=root)tree[fa].child[side]=pos;
		else root=pos;
	}
	int rank(int val) {
		int now=root,ans=0;
		while(now) {
			if(val<=val(now))now=ls(now);
			else {ans+=size(ls(now))+1;now=rs(now);}
		}
		return ans+1;
	}
	int kth(int rk) {
		int now=root;
		while(now>0&&rk>=0) {
			if(ls(now)&&size(ls(now))>=rk)now=ls(now);
			else {
				if(rk==size(ls(now))+1)return now;
				rk-=size(ls(now))+1;
				now=rs(now);
			}
		}
		return -1;
	}
	int pre(int num) {
		int now=root,ans=INT_MIN;
		while(now) {
			if(val(now)<num)ans=max(ans,val(now)),now=rs(now);
			else now=ls(now);
		}
		return ans;
	}
	int suc(int num) {
		int now=root,ans=INT_MAX;
		while(now) {
			if(val(now)>num)ans=min(ans,val(now)),now=ls(now);
			else now=rs(now);
		}
		return ans;
	}
} treap;

int main() {
	int q=Get_Int();
	while(q--) {
		int opt=Get_Int();
		if(opt==0)treap.insert(treap.root,Get_Int());
		else if(opt==1)treap.remove(Get_Int());
		else if(opt==2)printf("%d\n",treap.tree[treap.kth(Get_Int())].val);
		else if(opt==3)printf("%d\n",treap.rank(Get_Int())-1);
		else if(opt==4) {
			int ans=treap.pre(Get_Int());
			printf("%d\n",ans==INT_MIN?-1:ans);
		} else {
			int ans=treap.suc(Get_Int());
			printf("%d\n",ans==INT_MAX?-1:ans);
		}
	}
	return 0;
}