#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=50005;

struct Segment_Tree {
	struct Tree {
		int ls,rs,min;
		Tree() {ls=rs=0;min=INT_MAX/2;}
	} tree[maxn*50];
	int size;
#define mid ((left+right)>>1)
	void insert(int &index,int left,int right,int tar,int val) {
		if(right<tar||left>tar)return;
		if(!index)index=++size;
		tree[index].min=min(tree[index].min,val);
		if(left==right)return;
		insert(tree[index].ls,left,mid,tar,val);
		insert(tree[index].rs,mid+1,right,tar,val);
	}
	int query(int index,int left,int right,int Left,int Right) {
		if(!index||Right<left||Left>right)return INT_MAX/2;
		if(Left<=left&&Right>=right)return tree[index].min;
		return min(query(tree[index].ls,left,mid,Left,Right),query(tree[index].rs,mid+1,right,Left,Right));
	}
} st;

int n,q,root;
LL g,r,d[maxn],f[maxn];

int main() {
	n=Get_Int();
	g=Get_Int();
	r=Get_Int();
	for(int i=1; i<=n+1; i++)d[i]=d[i-1]+Get_Int();
	for(int i=n; i>0; i--) {
		int next=min(st.query(root,0,g+r,g+d[i]%(g+r),g+r-1+d[i]%(g+r)),st.query(root,0,g+r,d[i]%(g+r)-r,-1+d[i]%(g+r)));
		if(next==INT_MAX/2)f[i]=d[n+1]-d[i];
		else f[i]=f[next]+((d[next]-d[i]-1)/(g+r)+1)*(g+r);
		st.insert(root,0,g+r,d[i]%(g+r),i);
	}
	q=Get_Int();
	while(q--) {
		int t=Get_Int();
		int next=min(st.query(root,0,g+r,g-t%(g+r),g+r-1-t%(g+r)),st.query(root,0,g+r,g-t%(g+r)+(g+r),g+r-1-t%(g+r)+(g+r)));
		if(next==INT_MAX/2)printf("%lld\n",d[n+1]+t);
		else printf("%lld\n",f[next]+((d[next]+t-1)/(g+r)+1)*(g+r));
	}
	return 0;
}