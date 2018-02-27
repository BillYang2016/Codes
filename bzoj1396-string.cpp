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

const int maxn=500005,maxc=26;

struct SuffixAutomaton {
	int cnt,root,last;
	int next[maxn*2],Max[maxn*2],end_size[maxn*2],end_pos[maxn*2];
	int child[maxn*2][maxc],Bucket[maxn*2],top[maxn*2];
	SuffixAutomaton() {
		cnt=0;
		root=last=newnode(0);
	}
	int newnode(int val) {
		cnt++;
		next[cnt]=end_pos[cnt]=0;
		Max[cnt]=val;
		memset(child[cnt],0,sizeof(child[cnt]));
		return cnt;
	}
	void insert(int data,int pos) {
		int p=last,u=newnode(Max[last]+1);
		last=u;
		end_size[u]=1;
		end_pos[u]=pos;
		for(; p&&!child[p][data]; p=next[p])child[p][data]=u;
		if(!p)next[u]=root;
		else {
			int old=child[p][data];
			if(Max[old]==Max[p]+1)next[u]=old;
			else {
				int New=newnode(Max[p]+1);
				copy(child[old],child[old]+maxc,child[New]);
				next[New]=next[old];
				next[u]=next[old]=New;
				for(; child[p][data]==old; p=next[p])child[p][data]=New;
			}
		}
	}
	void build(string s) {
		int cnt=0;
		for(auto x:s)insert(x-'a',++cnt);
	}
	void topsort() {
		for(int i=1; i<=cnt; i++)Bucket[Max[i]]++;
		for(int i=1; i<=cnt; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=cnt; i++)top[Bucket[Max[i]]--]=i;
	}
	void get_end_pos() {
		topsort();
		for(int i=cnt; i>=1; i--) {
			int x=top[i];
			end_size[next[x]]+=end_size[x];
			end_pos[next[x]]=max(end_pos[next[x]],end_pos[x]);
		}
	}
} sam;

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

int main() {
	scanf("%s",s);
	int n=strlen(s);
	sam.build(s);
	sam.get_end_pos();
	int root1=st1.build(1,n),root2=st2.build(1,n);
	for(int i=1; i<=sam.cnt; i++)
		if(sam.end_size[i]==1) {
			int Max=sam.Max[i],Min=sam.Max[sam.next[i]],end=sam.end_pos[i];
			st1.modify(root1,end-Max+1,end-Min+1,end+1);
			st2.modify(root2,end-Min+1,end,Min);
		}
	for(int i=1; i<=n; i++)printf("%d\n",min(st1.query(1,i)-i,st2.query(1,i)));
	return 0;
} 
