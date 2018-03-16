#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

struct Tree {
	Tree *ls,*rs;
	int size,val;
	Tree(int l=0,int r=0) {size=r-l+1;}
} *root=Tree(-2e8,2e8);

struct Segment_Tree {
#define mid ((left+right)>>1)
	void newnode(Tree *&now,int left,int right) {if(!now)now=new Tree(left,right);}
	void insert(Tree *&now,int left,int right,int tar,int val) {
		newnode(now,left,right);
		if(left==right) {now->val=val;return;}
		newnode(ls,left,mid),newnode(rs,mid+1,right);
		if(tar<=ls->size)insert(now->ls,left,mid,tar,val);
		else insert(now->rs,mid+1,right,tar-ls->size,val);
	}
	void remove(Tree *&now,int left,int right,int tar) {
		if(!now)now=new Tree(left,right);
		now->size--;
		if(left==right)return;
		newnode(ls,left,mid),newnode(rs,mid+1,right);
		if(tar<=ls->size)remove(now->ls,left,mid,tar);
		else remove(now->rs,mid+1,right,tar-ls->size);
	}
	int query(Tree *&now,int left,int right,int tar) {
		if(!now)now=new Tree(left,right);
		if(left==right)return now->val?now->val:left;
		newnode(ls,left,mid),newnode(rs,mid+1,right);
		if(tar<=ls->size)return query(now->ls,left,mid,tar);
		else return query(now->rs,mid+1,right,tar-ls->size);
	}
	int sum(Tree *&now,int left,int right,int Left,int Right) {
		if(Right<left||Left>right)return 0;
		if(!now)now=new Tree(left,right);
		if(Left<=left&&Right>=right)return now->size;
		return sum(now->ls,left,mid,Left,Right)+sum(now->rs,mid+1,right,Left,Right);
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	int L=-2e8,R=2e8;
	for(int i=1; i<=m; i++) {
		int opt=Get_Int();
		if(opt==1) {
			int x=Get_Int()-ans,y=Get_Int()-ans;
			id[y]=id.count(x)?id[x]:x;
			st.insert(root,L,R,left-L+st.sum(root,L,R,left,id[y]),y);
		}
	}
	return 0;
}