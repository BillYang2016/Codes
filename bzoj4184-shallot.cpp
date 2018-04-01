#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005,MAX_BASE=31;

struct Linear_Bases {
	int b[MAX_BASE+1];
	Linear_Bases() {fill(b,b+MAX_BASE+1,0);}
	void add(int num) {
		for(int j=MAX_BASE; j>=0; j--)
			if(num>>j&1) {
				if(b[j]) {
					num^=b[j];
					continue;
				}
				b[j]=num;
				for(int k=j-1; k>=0; k--)if(b[j]>>k&1)b[j]^=b[k];
				for(int k=j+1; k<=MAX_BASE; k++)if(b[k]>>j&1)b[k]^=b[j];
				break;
			}
	}
	int cal() {
		int ans=0;
		for(int i=0; i<=MAX_BASE; i++)ans^=b[i];
		return ans;
	}
};

struct Segment_Tree {
	struct Tree {
		int left,right;
		vector<int> p;
		Tree(int l=0,int r=0):left(l),right(r) {p=vector<int>();}
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
	void insert(int index,int Left,int Right,int x) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {tree[index].p.push_back(x);return;}
		insert(ls,Left,Right,x);
		insert(rs,Left,Right,x);
	}
	void dfs(int index,Linear_Bases lb) {
		for(int x:tree[index].p)lb.add(x);
		if(tree[index].left==tree[index].right) {printf("%d\n",lb.cal());return;}
		dfs(ls,lb);
		dfs(rs,lb);
	}
} st;

int n,tot=0,a[maxn],b[maxn],H[maxn];

int main() {
	n=Get_Int();
	st.build(1,1,n);
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		if(a[i]>0)b[++tot]=a[i];
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1; i<=n; i++) {
		if(a[i]>0)H[lower_bound(b+1,b+tot+1,a[i])-b]=i;
		else {
			int now=lower_bound(b+1,b+tot+1,-a[i])-b;
			st.insert(1,H[now],i-1,-a[i]);
			H[now]=0;
		}
	}
	for(int i=1; i<=tot; i++)if(H[i])st.insert(1,H[i],n,b[i]);
	Linear_Bases lb;
	st.dfs(1,lb);
	return 0;
}