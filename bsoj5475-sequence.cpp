#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

#define pii pair<int,int>
#define inf INT_MAX

const int maxn=100005,maxm=1000005;

struct Segment_Tree {
	struct Tree {
		int left,right,min;
		Tree(int l=0,int r=0):left(l),right(r),min(inf) {}
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
#define mid ((tree[index].left+tree[index].right)>>1)
	void insert(int index,int tar,int val) {
		tree[index].min=min(tree[index].min,val);
		if(tree[index].left==tree[index].right)return;
		if(tar<=mid)insert(ls,tar,val);
		else insert(rs,tar,val);
	}
	pii query(int index,int tar,int val) { //>=tar,<=val
		if(tree[index].left==tree[index].right)return tree[index].min<=val?pii(tree[index].min,tree[index].left):pii(inf,inf);
		if(tar<=mid&&tree[ls].min<=val) {
			pii ans=query(ls,tar,val);
			if(ans.second!=inf)return ans;
		}
		return query(rs,tar,val);
	}
} st;

int n,m,ans[maxm];
pii a[maxn];

struct BIT {
	int c[maxn];
#define lowbit(x) x&(-x)
	void init() {for(int i=1; i<=n; i++)c[i]=inf;}
	void add(int x,int v) {for(int i=x; i>=1; i-=lowbit(i))c[i]=min(c[i],v);}
	int query(int x) {
		int ans=inf;
		for(int i=x; i<=n; i+=lowbit(i))ans=min(ans,c[i]);
		return ans;
	}
} bit;

struct node {
	int x,y,v,opt;
	node(int x=0,int y=0,int v=0,int o=1):x(x),y(y),v(v),opt(o) {}
	bool operator < (const node &b) const {return y<b.y||(y==b.y&&opt<b.opt);}
};

vector<node> p;

void find() {
	sort(a+1,a+n+1);
	st.build(1,1,n);
	for(int i=n; i>=1; i--) {
		int pos=a[i].second;
		pii next=st.query(1,pos+1,inf-1);
		while(next.second!=inf) {
			p.push_back(node(pos,next.second,abs(a[i].first-next.first),0));
			next=st.query(1,pos+1,(a[i].first+next.first-1)/2);
		}
		st.insert(1,pos,a[i].first);
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)a[i]=pii(Get_Int(),i);find();
	for(int i=1; i<=n; i++)a[i].first=inf/2-a[i].first;find();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int l=Get_Int(),r=Get_Int();
		p.push_back(node(l,r,i,1));
	}
	sort(p.begin(),p.end());
	bit.init();
	for(auto q:p) {
		if(q.opt==0)bit.add(q.x,q.v);
		else ans[q.v]=bit.query(q.x);
	}
	for(int i=1; i<=m; i++)printf("%d\n",ans[i]);
	return 0;
}