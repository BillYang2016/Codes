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

const int maxn=50005;

struct President_Tree {
	struct Tree {
		int ls,rs,sum;
	} tree[maxn*200];
	int step;

	int insert(int pre,int left,int right,int pos,int delta) {
		int now=++step;
		tree[now]=tree[pre];
		tree[now].sum+=delta;
		if(left==right)return now;
		int mid=(left+right)>>1;
		if(pos<=mid)tree[now].ls=insert(tree[pre].ls,left,mid,pos,delta);
		else tree[now].rs=insert(tree[pre].rs,mid+1,right,pos,delta);
		return now;
	}
	
	int query(int now,int left,int right,int target) {
		if(left>target)return 0;
		if(right<=target)return tree[now].sum;
		int mid=(left+right)>>1;
		return query(tree[now].ls,left,mid,target)+query(tree[now].rs,mid+1,right,target);
	}
} pt;

struct Point {
	int s,t,w;
	int pos;
	bool operator < (const Point& b) const {
		return pos<b.pos;
	}
} p[maxn],tmp[maxn];

int n,Ans[maxn],a[maxn],b[maxn],topl,topr,Sl[maxn],Sr[maxn],root[maxn];

int find(int v) {
	int Left=1,Right=topl;
	while(Left<=Right) {
		int mid=(Left+Right)>>1;
		if(p[Sl[mid]].pos<v)Left=mid+1;
		else Right=mid-1;
	}
	return Right;
}

void CDQBinary(int Left,int Right) {
	if(Left==Right)return;
	int mid=(Left+Right)>>1,lpos=Left,rpos=mid+1;
	for(int i=Left; i<=Right; i++)
		if(p[i].s<=mid)tmp[lpos++]=p[i];
		else tmp[rpos++]=p[i];
	for(int i=Left; i<=Right; i++)p[i]=tmp[i];
	CDQBinary(Left,mid);
	lpos=Left;
	topl=topr=0;
	for(int i=mid+1; i<=Right; i++) {
		while(lpos<=mid&&p[i].pos>p[lpos].pos) {
			while(topl&&p[lpos].s>p[Sl[topl]].s)topl--;
			Sl[++topl]=lpos;
			root[topl]=pt.insert(root[topl-1],1,n,p[lpos].t,p[lpos].w);
			lpos++;
		}
		while(topr&&p[i].s<p[Sr[topr]].s)topr--;
		if(topl)Ans[p[i].pos]+=pt.query(root[topl],1,n,p[i].t)-pt.query(root[find(p[Sr[topr]].pos)],1,n,p[i].t);
		Sr[++topr]=i;
	}
	CDQBinary(mid+1,Right);
	merge(p+Left,p+mid+1,p+mid+1,p+Right+1,tmp);
	int tot=0;
	for(int i=Left; i<=Right; i++)p[i]=tmp[tot++];
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		a[i]=p[i].s=Get_Int();
		b[i]=p[i].t=Get_Int();
		p[i].w=Get_Int();
		p[i].pos=i;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	int acnt=unique(a+1,a+n+1)-a-1,bcnt=unique(b+1,b+n+1)-b-1;
	for(int i=1; i<=n; i++) {
		p[i].s=lower_bound(a+1,a+acnt+1,p[i].s)-a;
		p[i].t=lower_bound(b+1,b+bcnt+1,p[i].t)-b;
	}
	CDQBinary(1,n);
	for(int i=1; i<=n; i++)printf("%d\n",Ans[i]);
	return 0;
} 
