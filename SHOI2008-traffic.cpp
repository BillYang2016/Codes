#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

bool Horizontal[maxn][2];

struct Segment_Tree {
	Segment_Tree *ls,*rs;
	Status S;
	int left,right;
	Segment_Tree(int l=0,int r=0):ls(NULL),rs(NULL),left(l),right(r),S(Status()) {}
	void build(int Left,int Right) {
		now=Tree(Left,Right);
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		ls=new Segment_Tree,rs=new Segment_Tree;
		ls->build(Left,mid);
		rs->build(mid+1,Right);
		push_up();
	}
#define mid ((left+right)>>1)
	void push_up() {
		S=merge(ls->S,Horizontal[mid],rs->S);
	}
	void modify_vertical(int target,bool val) {
		if(left>target||right<target)return;
		if(left==right) {
			S=Status(val);
			return;
		}
		ls->modify_vertical(target,val);
		rs->modify_vertical(target,val);
		push_up();
	}
	void modify_horizontal(int target) {
		if(target==mid) {
			push_up();
			return;
		}
		if(target<mid)ls->modify_horizontal(target);
		else rs->modify_horizontal(target);
		push_up();
	}
	void get_left_up(int &pos,Status &last,bool val) {
		if(left==right)return;
		if(pos<=mid)ls->get_left_up(pos,last,val);
		else {
			rs->get_left_up(pos,last,val);
			if(pos!=mid+1)return;
			Status now=merge(ls->S,Horizontal[mid],last);
			if(now[0][val]||now[1][val])pos=left,last=now;
			else ls->get_left_down(pos,last,val);
		}
	}
	void get_left_down(int &pos,Status &last,bool val) {
		if(left==right)return;
		Status now=merge(rs->S,Horizontal[right],last);
		if(now[0][val]||now[1][val]) {
			pos=mid+1;
			last=now;
			ls->get_left_down(pos,last,val);
		} else rs->get_left_down(pos,last,val);
	}
	void get_right_up(int &pos,Status &last,bool val) {
		if(left==right)return;
		if(pos>mid)rs->get_right_up(pos,last,val);
		else {
			ls->get_right_up(pos,last,val);
			if(pos!=mid)return;
			Status now=merge(last,Horizontal[mid],rs->S);
			if(now[val][0]||now[val][1])pos=right,last=now;
			else rs->get_right_down(pos,last,val);
		}
	}
	void get_right_down(int &pos,Status &last,bool val) {
		if(left==right)return;
		Status now=merge(last,Horizontal[left-1],ls->S);
		if(now[val][0]||now[val][1]) {
			pos=mid;
			last=now;
			rs->get_right_down(pos,last,val);
		} else ls->get_right_down(pos,last,val);
	}
	Status query(int Left,int Right) {
		if(Left==left&&Right==right)return S;
		if(Right<=mid)return ls->query(Left,Right);
		if(Left>mid)return rs->query(Left,Right);
		return merge(ls->query(Left,mid),Horizontal[mid],rs->query(mid+1,Right));
	}
} *root=new Segment_Tree;

void Modify(int x1,int y1,int x2,int y2,bool val) {
	if(x1==x2) { //横
		if(y1>y2)swap(y1,y2);
		a[y1][x1-1]=val;
		root->modify_horizontal(y1);
		return;
	} else root->modify_vertical(y1,val);
}

bool Query(int x1,int y1,int x2,int y2) {
	if(y1>y2)swap(x1,x2),swap(y1,y2);
	Status S;
	root->get_left_up(1,n,y1,S,x1-1);
	x1=S[0][x1-1]?1:2;
	S=Status();
	root->get_right_up(1,n,y2,S,x2-1);
	x2=S[x2-1][0]?1:2;
	S=root->query(y1,y2);
	return S[x1-1][x2-1];
}

int main() {
	n=Get_Int();
	root->build(1,n);
	while(true) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		int x1=Get_Int(),y1=Get_Int(),x2=Get_Int(),y2=Get_Int();
		if(opt=='C')Modify(x1,y1,x2,y2,false);
		else if(opt=='O')Modify(x1,y1,x2,y2,true);
		else if(opt=='A')printf("%d\n",Query(x1,y1,x2,y2)?'Y':'N');
		else break;
	}
	return 0;
} 
