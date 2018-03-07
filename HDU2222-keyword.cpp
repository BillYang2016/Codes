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
		int fail,cnt;
		void clear() {fill(child,child+26,0);fail=cnt=0;}
	} tree[maxn];
	int cnt;
#define ch(x,i) tree[x].child[i]
#define fail(x) tree[x].fail
	Aho_Corasick_Automaton() {init();}
	void init() {
		tree[cnt=0].clear();
	}
	int newnode() {
		tree[++cnt].clear();
		return cnt;
	}
	void insert(string s) {
		int now=0;
		for(char x:s) {
			int j=x-'a';
			if(!ch(now,j))ch(now,j)=newnode();
			now=ch(now,j);
		}
		tree[now].cnt++;
	}
	void buildfail() {
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<26; i++) {
				int &next=ch(now,i);
				if(next) {
					if(now)fail(next)=ch(fail(now),i);
					Q.push(next);
				} else next=ch(fail(now),i);
			}
		}
	}
	int match(string s) {
		int now=0,ans=0;
		for(auto x:s) {
			int j=x-'a';
			now=ch(now,j);
			for(int j=now; j; j=fail(j))ans+=tree[j].cnt,tree[j].cnt=0;
		}
		return ans;
	}
} acam;

int n;
char s[1000005];

int main() {
	int t=Get_Int();
	while(t--) {
		acam.init();
		n=Get_Int();
		for(int i=1; i<=n; i++) {
			scanf("%s",s);
			acam.insert(s);
		}
		acam.buildfail();
		scanf("%s",s);
		printf("%d\n",acam.match(s));
	}
	return 0;
}