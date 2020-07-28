#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
#define pii pair<int,int>
mt19937 g(rand());

int max(int a,int b) {return a>b?a:b;}

struct Treap { //root is interface 
	struct Tree {
		int l,r,size;
		int val,max;
		Tree(int s=0,int v=0):l(0),r(0),size(s),val(v),max(v) {}
	} tree[maxn<<1];
	int size;
#define ls(x) tree[x].l
#define rs(x) tree[x].r
#define val(x) tree[x].val
#define size(x) tree[x].size
	void init() {size=0;}
	int newnode(int v) {tree[++size]=Tree(1,v);return size;}
	void push_up(int x) {
		size(x)=size(ls(x))+size(rs(x))+1;
		tree[x].max=max(val(x),max(tree[ls(x)].max,tree[rs(x)].max));
	}
	pii split(int x,int num) {
		if(!x)return pii(0,0);
		if(num<=size(ls(x))) {
			pii lt=split(ls(x),num);
			ls(x)=lt.second;
			push_up(x);
			return pii(lt.first,x);
		} else {
			pii rt=split(rs(x),num-size(ls(x))-1);
			rs(x)=rt.first;
			push_up(x);
			return pii(x,rt.second);
		}
	}
	int merge(int a,int b) {
		if(!a||!b)return a+b;
		if(g()%(size(a)+size(b))<size(a)) {
			rs(a)=merge(rs(a),b);
			push_up(a);
			return a;
		} else {
			ls(b)=merge(a,ls(b));
			push_up(b);
			return b;
		}
	}
	int find_rank(int x,int k) {
		if(!x)return 0;
		if(k<=size(ls(x)))return find_rank(ls(x),k);
		else if(k==size(ls(x))+1)return x;
		else return find_rank(rs(x),k-size(ls(x))-1);
	}
	int insert(int x,int k,int v) {
		pii tmp=split(x,k-1);
		return merge(merge(tmp.first,newnode(v)),tmp.second);
	}
	int remove(int x,int k) {return merge(split(x,k-1).first,split(x,k).second);}
} bbt;
#undef size
#undef val
#undef ls
#undef rs
void Transform(int *a,int n,int k,int *ans) {
	int now=0,remain=n,tot=0,root=0;
	bbt.init();
	for(int i=1; i<=n; i++)root=bbt.insert(root,i,a[i]);
	while(remain) {
		int kth=(now+k)%remain;
		if(kth==0)kth=remain;
		int node=bbt.find_rank(root,kth);
		ans[++tot]=bbt.tree[node].val;
		root=bbt.remove(root,kth);
		remain--;
		now=kth-1;
	}
}
void per_power(int *in,int *out,int n,int k) {
	k --;
	static bool vis[maxn];
	for (int i=1;i<=n;i++) vis[i] = false;
	vector <vector<int> > cycle;
	for (int i=1;i<=n;i++) if (!vis[i]) {
		vector <int> cur;
		cur.push_back(i);
		vis[i] = true;
		int x = in[i];
		while (!vis[x]) {
			cur.push_back(x);
			vis[x] = true;
			x = in[x];
		}
		cycle.push_back(cur);
	}
	for (auto &x:cycle) {
		int sz = x.size();
		for (int i=0;i<sz;i++) out[x[i]] = in[x[(i+k)%sz]];
	}
}
void do_per(int *per,int *in,int *out,int n) {
	for (int i=1;i<=n;i++) {
		out[i] = in[per[i]];
	}
}
int raw[maxn],per_1[maxn],per_k[maxn];
bool vis[maxn];
int ans1[maxn],ans2[maxn];
int main() {
	int n,m;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) {
		raw[i] = i;
		ans1[i] = i;
	}
	bool cur = true;
	while (m --) {
		int k,x;
		scanf("%d%d",&k,&x);
		Transform(raw,n,k,per_1);
		per_power(per_1,per_k,n,x);
		if (cur) {
			do_per(per_k,ans1,ans2,n);
		}
		else {
			do_per(per_k,ans2,ans1,n);
		}
		cur ^= 1;
	}
	if (cur) {
		for (int i=1;i<=n;i++) printf("%d%c",ans1[i],i==n?'\n':' ');
	}
	else {
		for (int i=1;i<=n;i++) printf("%d%c",ans2[i],i==n?'\n':' ');
	}
	return 0;
}