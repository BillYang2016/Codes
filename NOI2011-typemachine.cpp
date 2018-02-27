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

const int maxn=200005;

struct Aho_Corasick_Automaton {
	struct Tree {
		int child[26],fail,fa;
		int cnt,id;
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
		for(int i=0; i<s.length(); i++) {
			int j=s[i]-'a';
			if(!ch(now,j))ch(now,j)=++cnt;
			now=ch(now,j);
		}
		tree[now].cnt++;
		return now;
	}
	
	void build(string s) {
		int now=root;
		for(auto x:s) {
			if(x=='P') {
				tree[now].id=++num;
				pos[num]=x;
			} else if(x=='B')now=tree[i].fa;
			else {
				int j=x-'a';
				if(!tree[now].child[j])tree[now].child[j]=++cnt,tree[cnt].fa=now;
				now=ch(now,j);
			}
		}
	}

	void buildfail() {
		queue<int>Q;
		Q.push(root);
		while(!Q.empty()) {
			int now=Q.front();
			AddEdge(tree[now].fail,now);
			Q.pop();
			for(int i=0; i<26; i++) {
				int& next=ch(now,i);
				if(!next) {
					next=ch(fail(now),i)?ch(fail(now),i):root;
					continue;
				}
				Q.push(next);
				int p=fail(now);
				while(p&&!ch(p,i))p=fail(p);
				if(p)fail(next)=ch(p,i);
				else fail(next)=root;
			}
		}
	}
	
	void dfs(int now) {
		First[now]=++step;
		for(int next:edges[Now])Dfs(next);
		Last[now]=step;
	}

	void query(string s) {
		int now=root;
		for(auto c:s) {
			if(c=='P') {
				int y=tree[now].id;
				for(auto Q:q[y])Ans[Q.id]=bit.sum(Last[pos[Q.id]])-bit.sum(First[pos[Q.id]]-1);
			} else if(x=='B') {
				bit.add(First[now],-1);
				now=tree[now].fa;
			} else {
				now=ch(now,c-'a');
				bit.add(First[now],1);
			}
		}
	}
} ac;

int main() {
	scanf("%s",s);
	ac.build(s);
	ac.buildfail();
	ac.dfs(1);
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		q[y].push_back((Query) {x,i});
	}
	ac.query(s);
	for(int i=1; i<=m; i++)printf("%d\n",Ans[i]);
	return 0;
} 
