#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxv=100000;

struct Segment_Tree {
	struct Tree {
		int ls,rs,max;
	} tree[maxn*100];
	int size;
#define mid ((left+right)>>1)
	void modify(int &index,int left,int right,int tar,int val) {
		if(!index)index=++size;
		tree[index].max=max(tree[index].max,val);
		if(left==right)return;
		if(tar<=mid)modify(tree[index].ls,left,mid,tar,val);
		else modify(tree[index].rs,mid+1,right,tar,val);
	}
	int query(int index,int left,int right,int Left,int Right) {
		if(!index||Right<left||Left>right)return 0;
		if(Left<=left&&Right>=right)return tree[index].max;
		return max(query(tree[index].ls,left,mid,Left,Right),query(tree[index].rs,mid+1,right,Left,Right));
	}
} st;

int n,m,a[maxn],f[maxn],Min[maxn],Max[maxn];

struct BIT {
	int root[maxn];
#define lowbit(x) x&(-x)
	void modify(int id) {
		for(int i=a[id]; i<=maxv; i+=lowbit(i))st.modify(root[i],1,maxv,Max[id],f[id]);
	}
	int query(int id) {
		int ans=0;
		for(int i=Min[id]; i>=1; i-=lowbit(i))ans=max(ans,st.query(root[i],1,maxv,1,a[id]));
		return ans;
	}
} bit;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)Max[i]=Min[i]=a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),v=Get_Int();
		Max[x]=max(Max[x],v);
		Min[x]=min(Min[x],v);
	}
	int ans=0;
	for(int i=1; i<=n; i++) {
		f[i]=bit.query(i)+1;
		ans=max(ans,f[i]);
		bit.modify(i);
	}
	printf("%d\n",ans);
	return 0;
}