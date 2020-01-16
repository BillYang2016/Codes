#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

typedef long long LL;

const int maxn=2000*2000+5,K=2;

int D;

struct Point {
	int d[K],Min[K],Max[K];
	int l,r;
	LL val,max,lazy;
	int& operator [] (int x) {return d[x];}
	bool operator < (const Point& b) const {return (d[D]<b.d[D])||(d[D]==b.d[D]&&d[D^1]<b.d[D^1]);}
} p[maxn];

struct KD_Tree {
	#define ls p[index].l
	#define rs p[index].r
	#define Min(i) p[index].Min[i]
	#define Max(i) p[index].Max[i]
	void push_up(int index) {
		for(int i=0; i<K; i++) {
			Min(i)=Max(i)=p[index][i];
			if(ls)Min(i)=min(Min(i),p[ls].Min[i]),Max(i)=max(Max(i),p[ls].Max[i]);
			if(rs)Min(i)=min(Min(i),p[rs].Min[i]),Max(i)=max(Max(i),p[rs].Max[i]);
		}
		p[index].max=p[index].val;
		if(ls)p[index].max=max(p[index].max,p[ls].max);
		if(rs)p[index].max=max(p[index].max,p[rs].max);
	}
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1,root=mid;
		D=now;
		nth_element(p+Left,p+mid,p+Right+1);
		if(Left<mid)p[root].l=build(Left,mid-1,now^1);
		if(Right>mid)p[root].r=build(mid+1,Right,now^1);
		push_up(root);
		return root;
	}
	void modify(int index,LL v) {
		p[index].val+=v;
		p[index].max+=v;
		p[index].lazy+=v;
	}
	void push_down(int index) {
		LL &v=p[index].lazy;
		if(!v)return;
		if(ls)modify(ls,v);
		if(rs)modify(rs,v);
		v=0;
	}
	void modify(int index,Point p1,Point p2,LL v,int now) {
		if(Min(now)>p2[now]||Max(now)<p1[now])return;
		if(Max(0)<=p2[0]&&Max(1)<=p2[1]&&Min(0)>=p1[0]&&Min(1)>=p1[1]) {
			modify(index,v);
			return;
		}
		push_down(index);
		if(p[index][0]<=p2[0]&&p[index][1]<=p2[1]&&p[index][0]>=p1[0]&&p[index][1]>=p1[1])p[index].val+=v;
		modify(ls,p1,p2,v,now^1);
		modify(rs,p1,p2,v,now^1);
		push_up(index);
	}
	LL query(int index,Point p1,Point p2,int now) {
		if(Min(now)>p2[now]||Max(now)<p1[now])return 0;
		if(Max(0)<=p2[0]&&Max(1)<=p2[1]&&Min(0)>=p1[0]&&Min(1)>=p1[1])return p[index].max;
		push_down(index);
		LL ans=0;
		if(p[index][0]<=p2[0]&&p[index][1]<=p2[1]&&p[index][0]>=p1[0]&&p[index][1]>=p1[1])ans=p[index].val;
		return max(ans,max(query(ls,p1,p2,now^1),query(rs,p1,p2,now^1)));
	}
	void dfs(int index) {
		push_down(index);
		if(ls)dfs(ls);
		if(rs)dfs(rs);
	}
} kdtree;

int n,m1,m2,root;

int id(int x,int y) {return (x-1)*n+y;}

int main() {
	n=Get_Int();
	m1=Get_Int();
	m2=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)p[id(i,j)][0]=i,p[id(i,j)][1]=j;
	root=kdtree.build(1,n*n,0);
	for(int i=1; i<=m1; i++) {
		int x1=Get_Int(),y1=Get_Int(),x2=Get_Int(),y2=Get_Int(),v=Get_Int();
		Point p1,p2;
		p1[0]=x1,p1[1]=y1;
		p2[0]=x2,p2[1]=y2;
		kdtree.modify(root,p1,p2,v,0);
	}
	for(int i=1; i<=m2; i++) {
		int x1=Get_Int(),y1=Get_Int(),x2=Get_Int(),y2=Get_Int();
		Point p1,p2;
		p1[0]=x1,p1[1]=y1;
		p2[0]=x2,p2[1]=y2;
		printf("%lld\n",kdtree.query(root,p1,p2,0));
	}
	return 0;
}