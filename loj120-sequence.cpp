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

#define pii pair<int,int>
mt19937 g(rand());

struct Treap {
	struct Tree {
		int l,r,size;
		int val;
		Tree(int s=0,int v=0):l(0),r(0),size(s),val(v) {}
	} tree[maxn*40];
	int size;
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define val(x) tree[x].val
#define size(x) tree[x].size
	int newnode(int v) {tree[++size]=Tree(1,v);return size;}
	void push_up(int x) {size(x)=size(ls(x))+size(rs(x))+1;}
	pii split(int x,int num) {
		if(!x)return pii(0,0);
		int now=++size;tree[now]=tree[x];
		if(num<=size(ls(x))) {
			pii lt=split(ls(x),num);
			ls(now)=lt.second;
			push_up(now);
			return pii(lt.first,now);
		} else {
			pii rt=split(rs(x),num-size(ls(x))-1);
			rs(now)=rt.first;
			push_up(now);
			return pii(now,rt.second);
		}
	}
	int merge(int a,int b) {
		if(a==0||b==0)return a+b;
		int now=++size;
		if(g()%(size(a)+size(b))<size(a)) {
			tree[now]=tree[a];
			rs(now)=merge(rs(a),b);
		} else {
			tree[now]=tree[b];
			ls(now)=merge(a,ls(b));
		}
		push_up(now);
		return now;
	}
	int insert(int x,int k,int v) {
		pii tmp=split(x,k-1);
		return merge(tmp.first,merge(newnode(v),tmp.second));
	}
	int remove(int x,int k) {return merge(split(x,k-1).first,split(x,k).second);}
	int find_rank(int x,int k) {
		if(!x)return 0;
		if(k<=size(ls(x)))return find_rank(ls(x),k);
		if(k==size(ls(x))+1)return x;
		return find_rank(rs(x),k-size(ls(x))-1);
	}
} treap;

int cnt=0,root[maxn];

int main() {
	srand(time(NULL)); 
	int q=Get_Int();
	while(q--) {
		int opt=Get_Int(),x=Get_Int(),y=Get_Int();
		if(opt==1)root[++cnt]=treap.insert(root[x],y,Get_Int());
		else if(opt==2)root[++cnt]=treap.remove(root[x],y);
		else printf("%d\n",treap.tree[treap.find_rank(root[x],y)].val);
	}
	return 0;
}