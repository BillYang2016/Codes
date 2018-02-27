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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=100005,maxt=4000005;

struct Trie {
	struct Tree {
		int ch[2],lazy,end;
	} tree[maxt];
	int cnt;
	Trie() {cnt=1;}
#define ls(now) tree[now].ch[0]
#define rs(now) tree[now].ch[1]
#define end(now) tree[now].end
#define lazy(now) tree[now].lazy
	void push_down(int now) {
		if(!ls(now))ls(now)=++cnt;
		if(!rs(now))rs(now)=++cnt;
		if(!end(ls(now)))lazy(ls(now))+=lazy(now);
		if(!end(rs(now)))lazy(rs(now))+=lazy(now);
		lazy(now)=0;
	}
	int insert(string s,int f) {
		int now=1;
		for(auto x:s) {
			push_down(now);
			now=tree[now].ch[x-'0'];
		}
		if(f)lazy(now)++,end(now)+=f;
		return lazy(now);
	}
} trie;

struct Modification {
	int opt;
	char s[35];
} a[maxn];

struct Query {
	int x,delta,id;
	char s[35];
	bool operator < (const Query& b) const {
		return x<b.x;
	}
} q[maxn<<1];

int n,m,cnt=0,ans[maxn];

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		char opt[5];
		scanf("%s%s",opt,a[i].s);
		a[i].opt=opt[0]=='A'?1:-1;
	}
	for(int i=1; i<=m; i++) {
		scanf("%s",q[++cnt].s);q[cnt].x=Get_Int();q[cnt].delta=-1;q[cnt].id=i;
		memcpy(q[cnt+1].s,q[cnt].s,sizeof(q[cnt].s));q[++cnt].x=Get_Int();q[cnt].delta=1;q[cnt].id=i;
	}
	sort(q+1,q+cnt+1);
	for(int i=1,j=1; i<=n; i++) {
		trie.insert(a[i].s,a[i].opt);
		for(; q[j].x==i; j++)ans[q[j].id]+=q[j].delta*trie.insert(q[j].s,0);
	}
	for(int i=1; i<=m; i++)printf("%d\n",ans[i]);
	return 0;
}