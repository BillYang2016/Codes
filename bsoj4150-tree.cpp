#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxm=300005;

int n,q,cnt=0,step=0,ans=0,root[maxm],a[maxn],Depth[maxn],father[maxn],Size[maxn],Son[maxn],Top[maxn],First[maxn],Last[maxn];
vector<int> edges[maxn];
map<int,int> M;

void Dfs1(int Now,int fa,int depth) {
	Depth[Now]=depth;
	father[Now]=fa;
	Size[Now]=1;
	for(int Next:edges[Now]) {
		if(Next==fa)continue;
		Dfs1(Next,Now,depth+1);
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Dfs2(int Now,int top) {
	Top[Now]=top;
	First[Now]=++step;
	if(Son[Now])Dfs2(Son[Now],top);
	for(int Next:edges[Now]) {
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
	Last[Now]=step;
}

int LCA(int x,int y) {
	for(; Top[x]!=Top[y]; x=father[Top[x]])if(Depth[Top[x]]<Depth[Top[y]])swap(x,y);
	return Depth[x]<Depth[y]?x:y;
}

struct Segment_Tree {
	struct Tree {
		int lson,rson,sum,tag;
	} tree[maxn*100];
	int size;
#define ls tree[index].lson
#define rs tree[index].rson
#define mid ((left+right)>>1)
	void modify(int &index,int val) {
		if(!index)index=++size;
		tree[index].sum+=val;
		tree[index].tag+=val;
	}
	void push_down(int index) {
		if(!tree[index].tag)return;
		modify(ls,tree[index].tag);
		modify(rs,tree[index].tag);
		tree[index].tag=0;
	}
	void modify(int &index,int left,int right,int Left,int Right,int val) {
		if(Right<left||Left>right)return;
		if(!index)index=++size;
		if(Left<=left&&Right>=right) {modify(index,val);return;}
		push_down(index);
		modify(ls,left,mid,Left,Right,val);
		modify(rs,mid+1,right,Left,Right,val);
	}
	int query(int index,int left,int right,int tar) {
		if(!index||left>tar||right<tar)return 0;
		if(left==right)return tree[index].sum;
		push_down(index);
		return query(ls,left,mid,tar)+query(rs,mid+1,right,tar);
	}
} st;

int main() {
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		if(!M.count(a[i]))M[a[i]]=++cnt;
		a[i]=M[a[i]];
	}
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	Dfs1(1,0,1);
	Dfs2(1,1); 
	for(int i=1; i<=n; i++)st.modify(root[a[i]],1,n,First[i],Last[i],1);
	while(q--) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		int x=Get_Int()^ans,y=Get_Int()^ans;
		if(opt=='C') {
			if(!M.count(y))M[y]=++cnt;
			y=M[y];
			st.modify(root[a[x]],1,n,First[x],Last[x],-1);
			st.modify(root[y],1,n,First[x],Last[x],1);
			a[x]=y;
		} else {
			int t=Get_Int()^ans;
			if(!M.count(t))M[t]=++cnt;
			t=M[t];
			int lca=LCA(x,y);
			ans=st.query(root[t],1,n,First[x])+st.query(root[t],1,n,First[y])-2*st.query(root[t],1,n,First[lca]);
			ans+=a[lca]==t;
			printf("%d\n",ans);
		}
	}
	return 0;
}