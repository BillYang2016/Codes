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

typedef long long LL;

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

const int maxn=2005;
const LL mod=1e9+7;

struct Aho_Corasick_Automaton {
	struct Tree {
		int child[10],fail,next,cnt;
		bool flag;
	} tree[maxn];
	int root,cnt;
	#define ch(x,i) tree[x].child[i]
	#define fail(x) tree[x].fail
	
	Aho_Corasick_Automaton() {
		init();
	}
	
	void init() {
		root=cnt=1;
		memset(tree,0,sizeof(tree));
	}
	
	int insert(string s) {
		int now=root;
		for(auto x:s) {
			int j=x-'0';
			if(!ch(now,j))ch(now,j)=++cnt;
			now=ch(now,j);
		}
		tree[now].cnt++;
		tree[now].flag=1;
		return now;
	}
	
	void buildfail() {
		queue<int>Q;
		Q.push(root);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<10; i++) {
				int& next=ch(now,i);
				if(!next) {
					next=ch(fail(now),i)?ch(fail(now),i):root;
					continue;
				}
				Q.push(next);
				int p=fail(now);
				if(p)fail(next)=ch(p,i);
				else fail(next)=root;
				tree[next].next=tree[fail(next)].cnt?fail(next):tree[fail(next)].next;
				tree[next].flag|=tree[tree[next].next].flag;
			}
		}
	}
} acam;

char n[maxn];
int len,m;
LL f[maxn][maxn]; 

LL Dp(int Now,int pos,bool up,bool zero) {
	if(acam.tree[pos].flag)return 0;
	if(Now==len)return !zero;
	if(!zero&&!up&&~f[Now][pos])return f[Now][pos];
	int limit=up?n[Now]-'0':9;
	LL sum=0;
	for(int i=0; i<=limit; i++) {
		bool _zero=zero&&i==0;
		sum=(sum+Dp(Now+1,_zero?1:acam.tree[pos].child[i],up&&i==limit,_zero))%mod;
	}
	if(!zero&&!up)f[Now][pos]=sum;
	return sum;
}

int main() {
	memset(f,-1,sizeof(f));
	scanf("%s",n);
	len=strlen(n);
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		char s[maxn];
		scanf("%s",s);
		int len=strlen(s);
		acam.insert(s);
	}
	acam.buildfail();
	printf("%lld\n",Dp(0,1,1,1));
	return 0;
}
