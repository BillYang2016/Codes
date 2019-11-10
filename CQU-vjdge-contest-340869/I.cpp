#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;

int n,m,cnt=0,First[maxn],Last[maxn];
bool vst[maxn];

vector<int> G[maxn];

struct Segment_Tree {
	struct Tree {
		int left,right,val,lazy;
		Tree(int l=0,int r=0):left(l),right(r),val(-1),lazy(0) {}
	} tree[maxn<<2];
	#define ls index<<1
	#define rs (index<<1)+1
	void modify(int index,int val) {tree[index].val=tree[index].lazy=val;}
	void push_down(int index) {
		if(!tree[index].lazy)return;
		int &lazy=tree[index].lazy;
		modify(ls,lazy);
		modify(rs,lazy);
		lazy=0;
	}
	void build(int index,int Left,int Right) {
		tree[index]=Tree(Left,Right);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void modify(int index,int Left,int Right,int val) {
		if(Right<tree[index].left||Left>tree[index].right)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {modify(index,val);return;}
		push_down(index);
		modify(ls,Left,Right,val);
		modify(rs,Left,Right,val);
	}
	int query(int index,int pos) {
		if(pos<tree[index].left||pos>tree[index].right)return -1;
		if(tree[index].left==tree[index].right)return tree[index].val;
		push_down(index);
		return max(query(ls,pos),query(rs,pos));
	}
} st;

void Clear() {
	for(int i=1; i<=n; i++)G[i].clear();
	memset(vst,0,sizeof(vst));
	cnt=0;
}

void AddEdge(int x,int y) {G[x].push_back(y);}

void Dfs(int Now) {
	First[Now]=++cnt;
	for(int Next:G[Now])Dfs(Next);
	Last[Now]=cnt;
}

int main() {
	int t=Get_Int();
	for(int k=1; k<=t; k++) {
		printf("Case #%d:\n",k);
		n=Get_Int();
		Clear();
		for(int i=1; i<n; i++) {
			int x=Get_Int(),y=Get_Int();
			AddEdge(y,x);
			vst[x]=1;
		}
		int root=0;
		for(int i=1; i<=n; i++)if(!vst[i]) {root=i;break;}
		Dfs(root);
		st.build(1,1,n);
		m=Get_Int();
		for(int i=1; i<=m; i++) {
			char c=getchar();
			while(!isalpha(c))c=getchar();
			if(c=='C') {
				int x=Get_Int();
				printf("%d\n",st.query(1,First[x]));
			} else {
				int x=Get_Int(),y=Get_Int();
				st.modify(1,First[x],Last[x],y);
			}
		}
	}
	return 0;
}