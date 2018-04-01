#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,K=20;

struct Edge {int from,to;string s;};
int n,q,root[maxn],Depth[maxn],p[maxn][K];
vector<Edge> edges[maxn];

void AddEdge(int x,int y,string s) {edges[x].push_back((Edge) {x,y,s});}

struct Trie {
	struct Tree {
		int child[26],size;
	} tree[maxn*20];
	int size;
#define ch(x,i) tree[x].child[i]
	void insert(int &now,int pre,int dep,string s) {
		tree[now=++size]=tree[pre];
		tree[now].size++;
		if(dep<s.length())insert(ch(now,s[dep]-'a'),ch(pre,s[dep]-'a'),dep+1,s);
	}
	int query(int x,string s) {
		int now=root[x];
		for(auto x:s) {
			int ch=x-'a';
			if(!ch(now,ch))return 0;
			now=ch(now,ch);
		}
		return tree[now].size;
	}
} trie;

void Dfs(int Now,int fa,int depth) {
	Depth[Now]=Depth[fa]+1;
	p[Now][0]=fa;
	for(int i=1; i<K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		trie.insert(root[Next],root[Now],0,e.s);
		Dfs(Next,Now,depth+1);
	}
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)if(p[a][i]!=p[b][i])a=p[a][i],b=p[b][i];
	return p[a][0];
}

char s[15];

int main() {
	scanf("%d",&n);
	for(int i=1; i<n; i++) {
		int x,y;
		scanf("%d%d%s",&x,&y,s);
		AddEdge(x,y,s);
		AddEdge(y,x,s);
	}
	Dfs(1,0,0);
	scanf("%d",&q);
	while(q--) {
		int x,y;
		scanf("%d%d%s",&x,&y,s);
		printf("%d\n",trie.query(x,s)+trie.query(y,s)-2*trie.query(LCA(x,y),s));
	}
	return 0;
}