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

const int maxn=100005,K=3;

int D,Left[K],Right[K],ans=0;

struct KD_Tree {
	struct Point {
		int d[K],Min[K],Max[K];
		int ls,rs,val,max;
		int& operator [] (int x) {
			return d[x];
		}
		Point(int x=0,int y=0,int z=0,int v=0) {
			ls=rs=0;
			d[0]=Min[0]=Max[0]=x;
			d[1]=Min[1]=Max[1]=y;
			d[2]=Min[2]=Max[2]=z;
			val=max=v;
		}
		bool operator < (const Point& b) const {
			return d[D]<b.d[D];
		}
	} p[maxn];
#define lson p[index].ls
#define rson p[index].rs
	int build(int Left,int Right,int now) {
		int mid=(Left+Right)>>1,root=mid;
		D=now;
		nth_element(p+Left,p+mid,p+Right+1);
		if(Left<mid)p[root].ls=build(Left,mid-1,(now+1)%K);
		if(Right>mid)p[root].rs=build(mid+1,Right,(now+1)%K);
		push_up(root);
		return root;
	}
	void push_up(int index) {
		if(lson)p[index].max=max(p[index].max,p[lson].max);
		if(rson)p[index].max=max(p[index].max,p[rson].max);
		for(int i=0; i<K; i++) {
			if(lson) {
				p[index].Min[i]=min(p[index].Min[i],p[lson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[lson].Max[i]);
			}
			if(rson) {
				p[index].Min[i]=min(p[index].Min[i],p[rson].Min[i]);
				p[index].Max[i]=max(p[index].Max[i],p[rson].Max[i]);
			}
		}
	}
	bool inspace(Point p) {
		for(int i=0; i<K; i++)
			if(p[i]<Left[i]||p[i]>Right[i])return false;
		return true;
	}
	bool check(int index) {
		if(!index)return 0;
		if(p[index].Max[0]<Left[0]||p[index].Min[0]>Right[0])return 0;
		if(p[index].Min[1]>Right[1]||p[index].Max[2]<Left[2])return 0;
		return 1;
	}
	void query(int index) {
		if(!index)return;
		if(inspace(p[index]))ans=max(ans,p[index].val);
		bool lable=check(lson),rable=check(rson);
		if(p[lson].max>p[rson].max) {
			if(lable&&p[lson].max>=ans)query(lson);
			if(rable&&p[rson].max>=ans)query(rson);
		} else {
			if(rable&&p[rson].max>=ans)query(rson);
			if(lable&&p[lson].max>=ans)query(lson);
		}
	}
} kdtree;

int n,m,lastans=0,a[maxn],Pre[maxn],Next[maxn],Hash[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		Pre[i]=Hash[a[i]];
		Hash[a[i]]=i;
	}
	for(int i=1; i<=n; i++)Hash[i]=n+1;
	for(int i=n; i>=1; i--) {
		Next[i]=Hash[a[i]];
		Hash[a[i]]=i;
	}
	for(int i=1; i<=n; i++)kdtree.p[i]=KD_Tree::Point(i,Pre[i],Next[i],a[i]);
	int root=kdtree.build(1,n,0);
	for(int i=1; i<=m; i++) {
		int x=(Get_Int()+lastans)%n+1,y=(Get_Int()+lastans)%n+1;
		if(x>y)swap(x,y);
		Left[0]=x,Left[1]=0,Left[2]=y+1;
		Right[0]=y,Right[1]=x-1,Right[2]=n+1;
		ans=0;
		kdtree.query(root);
		lastans=ans;
		printf("%d\n",ans);
	}
	return 0;
} 
