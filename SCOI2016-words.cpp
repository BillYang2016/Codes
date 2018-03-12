#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=510005;

vector<int> edges[maxn];
int n;
long long Size[maxn],f[maxn];
char s[maxn];

struct Trie {
	int child[maxn][26],end[maxn],cnt;
	void insert(string s,int id) {
		int now=0;
		for(char x:s) {
			int ch=x-'a';
			if(!child[now][ch])child[now][ch]=++cnt;
			now=child[now][ch];
		}
		end[now]=id;
	}
	void build(int now,int id) {
		if(end[now])edges[id].push_back(end[now]);
		for(int i=0; i<26; i++)if(child[now][i])build(child[now][i],end[now]?end[now]:id);
	}
} trie;

bool cmp(int x,int y) {
	return Size[x]<Size[y];
}

void Dfs(int Now) {
	Size[Now]=f[Now]=1;
	for(int Next:edges[Now]) {
		Dfs(Next);
		Size[Now]+=Size[Next];
	}
	sort(edges[Now].begin(),edges[Now].end(),cmp);
	int tmp=0;
	for(int Next:edges[Now])f[Now]+=f[Next]+tmp,tmp+=Size[Next];
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		scanf("%s",s);
		int len=strlen(s);
		reverse(s,s+len);
		trie.insert(s,i);
	}
	trie.build(0,0);
	Dfs(0);
	printf("%lld\n",f[0]-1);
	return 0;
}