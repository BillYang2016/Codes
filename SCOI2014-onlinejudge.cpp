#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int L=-2e8,R=2e8; //boundary limit

struct Tree {
	Tree *ls,*rs;
	int size,val;
	Tree(int l=0,int r=0) {size=r-l+1;}
} *root=new Tree(L,R);

struct Segment_Tree {
#define mid ((left+right)>>1)
	void newnode(Tree *&now,int left,int right) {if(!now)now=new Tree(left,right);}
	void insert(Tree *&now,int left,int right,int tar,int val) {
		newnode(now,left,right);
		if(left==right) {now->val=val;return;}
		newnode(now->ls,left,mid),newnode(now->rs,mid+1,right);
		if(tar<=now->ls->size)insert(now->ls,left,mid,tar,val);
		else insert(now->rs,mid+1,right,tar-now->ls->size,val);
	}
	void remove(Tree *&now,int left,int right,int tar) {
		if(!now)now=new Tree(left,right);
		now->size--;
		if(left==right)return;
		newnode(now->ls,left,mid),newnode(now->rs,mid+1,right);
		if(tar<=now->ls->size)remove(now->ls,left,mid,tar);
		else remove(now->rs,mid+1,right,tar-now->ls->size);
	}
	int query(Tree *&now,int left,int right,int tar) {
		if(!now)now=new Tree(left,right);
		if(left==right)return now->val?now->val:left;
		newnode(now->ls,left,mid),newnode(now->rs,mid+1,right);
		if(tar<=now->ls->size)return query(now->ls,left,mid,tar);
		else return query(now->rs,mid+1,right,tar-now->ls->size);
	}
	int sum(Tree *&now,int left,int right,int Left,int Right) {
		if(Right<left||Left>right)return 0;
		if(!now)now=new Tree(left,right);
		if(Left<=left&&Right>=right)return now->size;
		return sum(now->ls,left,mid,Left,Right)+sum(now->rs,mid+1,right,Left,Right);
	}
} st;

map<int,int> id;
int n,m,ans=0;

int main() {
	n=Get_Int();
	m=Get_Int();
	int left=1,right=n;
	for(int i=1; i<=m; i++) {
		int opt=Get_Int();
		if(opt==1) {
			int x=Get_Int()-ans,y=Get_Int()-ans;
			id[y]=id.count(x)?id[x]:x;
			st.insert(root,L,R,st.sum(root,L,R,L,id[y]),y); //insert at id[y]
			printf("%d\n",ans=st.sum(root,L,R,left,id[y]));
		} else if(opt==2) {
			int x=Get_Int()-ans;
			ans=st.sum(root,L,R,left,id.count(x)?id[x]:x);
			printf("%d\n",ans);
			st.remove(root,L,R,left-L+ans);
			st.insert(root,L,R,left-L,x);
			id[x]=--left;
		} else if(opt==3) {
			int x=Get_Int()-ans;
			ans=st.sum(root,L,R,left,id.count(x)?id[x]:x);
			printf("%d\n",ans);
			st.remove(root,L,R,left-L+ans);
			st.insert(root,L,R,st.sum(root,L,R,L,right)+1,x);
			id[x]=++right;
		} else {
			int k=Get_Int()-ans;
			printf("%d\n",ans=st.query(root,L,R,left-L+k));
		}
	}
	return 0;
}