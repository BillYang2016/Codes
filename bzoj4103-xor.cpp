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

const int maxn=300005,maxb=35;

struct Query {
	int l,r,v;
	Query(int _l=0,int _r=0,int _v=0):l(_l),r(_r),v(_v) {}
};

vector<Query> Q;

struct Trie {
	struct Tree {
		int child[2],size;
	} tree[maxn*maxb];
	int size;
	int insert(int pre,int v,int depth) {
		int now=++size;
		tree[now]=tree[pre];
		tree[now].size++;
		if(depth<0)return now;
		int x=v>>depth&1;
		tree[now].child[x]=insert(tree[pre].child[x],v,depth-1);
		return now; 
	}
	int ans;
	void query(int depth,int k) {
		int sum=0;
		bool bj=0;
		for(auto q:Q) {
			int x=q.v>>depth&1;
			sum+=tree[tree[q.r].child[x^1]].size-tree[tree[q.l].child[x^1]].size;
		}
		if(sum>=k) {
			ans+=1<<depth;
			bj=1;
		} else k-=sum;
		for(auto& q:Q) {
			int x=q.v>>depth&1;
			q.l=tree[q.l].child[x^bj];
			q.r=tree[q.r].child[x^bj];
		}
		if(depth&&k)query(depth-1,k);
	}
} trie;

int n,m,q,a[maxn],b[maxn],root[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		b[i]=Get_Int();
		root[i]=trie.insert(root[i-1],b[i],30);
	}
	q=Get_Int();
	for(int i=1; i<=q; i++) {
		int u=Get_Int(),d=Get_Int(),l=Get_Int(),r=Get_Int(),k=Get_Int();
		Q.clear();
		trie.ans=0;
		for(int j=u; j<=d; j++)Q.push_back(Query(root[l-1],root[r],a[j]));
		trie.query(30,k);
		printf("%d\n",trie.ans);
	}
	return 0;
} 
