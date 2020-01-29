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

struct Aho_Corasick_Automaton {
	struct Tree {
		int child[26];
		int fail,next;
		int value,length;
		bool flag;
		void clear() {fill(child,child+26,0);fail=flag=next=length=0;value=INT_MAX;}
	} tree[maxn];
	int cnt;
#define ch(x,i) tree[x].child[i]
#define fail(x) tree[x].fail
#define next(x) tree[x].next
	Aho_Corasick_Automaton() {init();}
	void init() {tree[cnt=0].clear();}
	int newnode() {tree[++cnt].clear();return cnt;}
	void insert(char *s,int v) {
		int now=0,len=strlen(s);
		for(int i=0; i<len; i++) {
			int j=s[i]-'a';
			if(!ch(now,j))ch(now,j)=newnode();
			now=ch(now,j);
		}
		tree[now].flag=1;
		tree[now].value=min(tree[now].value,v);
		tree[now].length=len;
	}
	void buildfail() {
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<26; i++) {
				int &son=ch(now,i);
				if(!son) {
					son=now?ch(fail(now),i):0;
					continue;
				}
				fail(son)=now?ch(fail(now),i):0;
				next(son)=tree[fail(son)].flag?fail(son):next(fail(son));
				Q.push(son);
			}
		}
	}
} acam;

char s[maxn];
long long f[maxn];
int n;

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		scanf("%s",s);
		acam.insert(s,Get_Int());
	}
	acam.buildfail();
	scanf("%s",s+1);
	n=strlen(s+1);
	int Now=0;
	for(int i=1; i<=n; i++) {
		f[i]=LLONG_MAX/2;
		Now=acam.tree[Now].child[s[i]-'a'];
		for(int j=Now; j; j=acam.tree[j].next) {
			f[i]=min(f[i],f[i-acam.tree[j].length]+acam.tree[j].value);
		}
	}
	printf("%lld\n",f[n]==LLONG_MAX/2?-1:f[n]);
	return 0;
}