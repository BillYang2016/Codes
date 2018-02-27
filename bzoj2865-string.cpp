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

const int maxn=500005;

int sa[maxn],Rank[maxn],First[maxn],Second[maxn],Bucket[maxn],tmp[maxn],Height[maxn];

void Suffix_Array(int n,int* a) {
	fill(Bucket,Bucket+n+1,0);
	for(int i=1; i<=n; i++)Bucket[a[i]]++;
	for(int i=1; i<=n; i++)Bucket[i]+=Bucket[i-1]; 
	for(int i=1; i<=n; i++)Rank[i]=Bucket[a[i]-1]+1;
	for(int t=1; t<=n; t*=2) { 
		for(int i=1; i<=n; i++) {
			First[i]=Rank[i];
			Second[i]=(i+t)>n?0:Rank[i+t];
		}
		fill(Bucket,Bucket+n+1,0);
		for(int i=1; i<=n; i++)Bucket[Second[i]]++;
		for(int i=1; i<=n; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=n; i++)tmp[n-(--Bucket[Second[i]])]=i;
		fill(Bucket,Bucket+n+1,0);
		for(int i=1; i<=n; i++)Bucket[First[i]]++;
		for(int i=1; i<=n; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=n; i++)sa[Bucket[First[tmp[i]]]--]=tmp[i];
		bool unique=true;
		for(int j=1,last=0; j<=n; j++) {
			int i=sa[j];
			if(!last)Rank[i]=1;
			else if(First[i]==First[last]&&Second[i]==Second[last])Rank[i]=Rank[last],unique=false;
			else Rank[i]=Rank[last]+1; 
			last=i;
		}
		if(unique)break; 
	}
	int k=0;
	for(int i=1; i<=n; i++) {
		if(Rank[i]==1)k=0;
		else {
			if(k>0)k--;
			int j=sa[Rank[i]-1];
			while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k])k++; 
		}
		Height[Rank[i]]=k;
	}
}

struct Segment_Tree {
	struct Tree {
		int ls,rs;
		int left,right;
		int min,lazy;
		Tree(int l=0,int r=0):left(l),right(r) {
			ls=rs=0;
			min=lazy=INT_MAX/2;
		}
	} tree[maxn<<1];
	int size;
#define ls tree[index].ls
#define rs tree[index].rs
	int build(int Left,int Right) {
		int index=++size;
		tree[index]=Tree(Left,Right);
		if(Left==Right)return index;
		int mid=(Left+Right)>>1;
		ls=build(Left,mid);
		rs=build(mid+1,Right);
		return index;
	}
	void push_up(int index) {
		tree[index].min=min(tree[ls].min,tree[rs].min);
	}
	void modify(int index,int val) {
		tree[index].min=min(tree[index].min,val);
		tree[index].lazy=min(tree[index].lazy,val);
	}
	void push_down(int index) {
		if(tree[index].left==tree[index].right||tree[index].lazy==INT_MAX/2)return;
		modify(ls,tree[index].lazy);
		modify(rs,tree[index].lazy);
		tree[index].lazy=INT_MAX/2;
	}
	void modify(int index,int Left,int Right,int val) {
		if(Left>tree[index].right||Right<tree[index].left)return;
		if(Left<=tree[index].left&&Right>=tree[index].right) {
			modify(index,val);
			return;
		}
		push_down(index);
		modify(ls,Left,Right,val);
		modify(rs,Left,Right,val);
		push_up(index);
	}
	int query(int index,int target) {
		if(target>tree[index].right||target<tree[index].left)return INT_MAX/2;
		if(tree[index].left==tree[index].right)return tree[index].min;
		push_down(index);
		return min(query(ls,target),query(rs,target));
	}
} st1,st2;

char s[maxn];
int n,a[maxn];

int main() {
	scanf("%s",s+1);
	n=strlen(s+1);
	for(int i=1; i<=n; i++)a[i]=s[i]-'a'+1;
	Suffix_Array(n,a);
	int root1=st1.build(1,n),root2=st2.build(1,n);
	for(int i=1; i<=n; i++) {
		int len=max(Height[i],Height[i+1]);
		if(sa[i]+len<=n)st1.modify(1,sa[i],sa[i]+len,len+1);
		st2.modify(1,sa[i]+len+1,n,1-sa[i]);
	}
	for(int i=1; i<=n; i++)printf("%d\n",min(st1.query(1,i),st2.query(1,i)+i));
	return 0;
}
