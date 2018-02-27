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

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
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

struct Point {
	LL x,y;
	Point(LL _x=0,LL _y=0):x(_x),y(_y) {}
	Point operator - (const Point& b) const {
		return Point(b.x-x,b.y-y);
	}
	bool operator < (const Point& b) const {
		return x<b.x||(x==b.x&&y<b.y);
	}
};

typedef Point Vector;

LL Cross(Vector a,Vector b) {
	return a.x*b.y-a.y*b.x;
}

LL Dot(Vector a,Vector b) {
	return a.x*b.x+a.y*b.y;
}

const int maxn=400005;

struct Segment_Tree {
	struct Tree {
		int left,right;
		vector<Point> up,down;
	} tree[maxn<<4];
#define ls index<<1
#define rs index<<1|1
	void build(int index,int Left,int Right) {
		tree[index].left=Left,tree[index].right=Right;
		if(Left==Right)return;
		int mid=(Left+Right)>>1;
		build(ls,Left,mid);
		build(rs,mid+1,Right);
	}
	void merge_up(int index) {
		tree[index].up.resize(tree[ls].up.size()+tree[rs].up.size());
		std::merge(tree[ls].up.begin(),tree[ls].up.end(),tree[rs].up.begin(),tree[rs].up.end(),tree[index].up.begin());
		vector<Point> tmp;
		for(auto x:tree[index].up) {
			while(tmp.size()>=2&&Cross(tmp[tmp.size()-2]-tmp.back(),tmp.back()-x)>=0)tmp.pop_back();
			tmp.push_back(x);
		}
		tree[index].up=tmp;
	}
	void merge_down(int index) {
		tree[index].down.resize(tree[ls].down.size()+tree[rs].down.size());
		std::merge(tree[ls].down.begin(),tree[ls].down.end(),tree[rs].down.begin(),tree[rs].down.end(),tree[index].down.begin());
		vector<Point> tmp;
		for(auto x:tree[index].down) {
			while(tmp.size()>=2&&Cross(tmp[tmp.size()-2]-tmp.back(),tmp.back()-x)>=0)tmp.pop_back();
			tmp.push_back(x);
		}
		tree[index].down=tmp;
	}
	void merge(int index) {
		merge_up(index);
		merge_down(index);
	}
	void insert(int index,int target,Point p) {
		if(tree[index].left>target||tree[index].right<target)return;
		if(tree[index].left==tree[index].right) {
			tree[index].up.push_back(p);
			tree[index].down.push_back(p);
			return;
		}
		insert(ls,target,p);
		insert(rs,target,p);
		if(target==tree[index].right)merge(index);
	}
	LL trisection(const vector<Point>& p,Vector x) {
		int Left=0,Right=p.size()-1;
		while(Right-Left>2) {
			int lmid=Left+(Right-Left)/3,rmid=Right-(Right-Left)/3;
			if(Dot(p[lmid],x)>Dot(p[rmid],x))Right=rmid;
			else Left=lmid;
		}
		LL ans=-LLONG_MAX;
		for(int i=Left; i<=Right; i++)ans=max(ans,Dot(p[i],x));
		return ans;
	}
	LL trisection(int index,Vector x) {
		if(x.y>0)return trisection(tree[index].up,x);
		else return trisection(tree[index].down,x);
	}
	LL query(int index,int Left,int Right,Vector vec) {
		if(Right<tree[index].left||Left>tree[index].right)return -LLONG_MAX;
		if(Left<=tree[index].left&&Right>=tree[index].right)return trisection(index,vec);
		return max(query(ls,Left,Right,vec),query(rs,Left,Right,vec));
	}
} st;

int q,cnt=0;
LL lastans=0;
char s;

int decode(int x) {
	return x^(lastans&0x7fffffff);
}

int main() {
	q=Get_Int();
	while(!isalpha(s))s=getchar();
	st.build(1,1,q);
	for(int i=1; i<=q; i++) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		LL x=Get_Int(),y=Get_Int();
		if(s!='E')x=decode(x),y=decode(y);
		if(opt=='Q') {
			int l=Get_Int(),r=Get_Int();
			if(s!='E')l=decode(l),r=decode(r);
			lastans=st.query(1,l,r,Vector(x,y));
			printf("%lld\n",lastans);
		} else st.insert(1,++cnt,Vector(x,y));
	}
	return 0;
} 
