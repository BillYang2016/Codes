#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005;

int n,m,ans=INT_MAX,id,f[maxn],g[maxn],InDegree[maxn],OutDegree[maxn];
vector<int> top,edges[maxn],fedges[maxn];

void topsort() {
	queue<int> Q;
	for(int i=1; i<=n; i++)if(!InDegree[i])Q.push(i);
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		top.push_back(Now);
		for(int Next:edges[Now]) {
			f[Next]=max(f[Next],f[Now]+1);
			InDegree[Next]--;
			if(!InDegree[Next])Q.push(Next);
		}
	}
	Q=queue<int>();
	for(int i=1; i<=n; i++)if(!OutDegree[i])Q.push(i);
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		for(int Next:fedges[Now]) {
			g[Next]=max(g[Next],g[Now]+1);
			OutDegree[Next]--;
			if(!OutDegree[Next])Q.push(Next);
		}
	}
}

struct Segment_Tree {
	struct Tree {
		int size,max;
	} tree[maxn<<2];
#define ls index<<1
#define rs index<<1|1
	void insert(int index,int left,int right,int val,int delta) {
		if(left==right) {
			tree[index].size+=delta;
			if(tree[index].size)tree[index].max=left;
			else tree[index].max=INT_MIN/2;
			return;
		}
		int mid=(left+right)>>1;
		if(val<=mid)insert(ls,left,mid,val,delta);
		else insert(rs,mid+1,right,val,delta);
		tree[index].max=max(tree[ls].max,tree[rs].max);
	}
} st;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		InDegree[y]++;
		OutDegree[x]++;
		edges[x].push_back(y);
		fedges[y].push_back(x);
	}
	topsort();
	for(int i=1; i<=n; i++)st.insert(1,0,n,g[i],1);
	for(int Now:top) {
		for(int Next:fedges[Now])st.insert(1,0,n,f[Next]+1+g[Now],-1);
		st.insert(1,0,n,g[Now],-1);
		if(st.tree[1].max!=INT_MIN/2&&ans>st.tree[1].max)ans=st.tree[1].max,id=Now;
		for(int Next:edges[Now])st.insert(1,0,n,f[Now]+1+g[Next],1);
		st.insert(1,0,n,f[Now],1);
	}
	printf("%d %d\n",id,ans);
	return 0;
}