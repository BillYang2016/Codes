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

void Dfs(int Now,int fa,int depth) {
	Size[Now]=1;
	father[Now]=fa;
	Depth[Now]=depth;
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		ch[Next]=e.ch;
		Dfs(Next,Now,depth+1);
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Dfs2(int Now,int top) {
	Dfn[Now]=++step;
	M[step]=Now;
	Top[Now]=top;
	if(Son[Now])Dfs2(Son[Now],top);
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==father[Now]||Next==Son[Now])continue;
		Dfs2(Next,Next);
	}
}

int LCA(int x,int y) {
	for(; Top[x]!=Top[y]; x=father[Top[x]])if(Depth[Top[x]]<Depth[Top[y]])swap(x,y);
	return Depth[x]<Depth[y]?x:y;
}

int kth(int x,int k) { //k倍祖先
	while(k>Depth[x]-Depth[Top[x]])k-=Depth[x]-Depth[Top[x]]+1,x=father[Top[x]];
	return M[Dfn[Now]-k];
}

struct KMP {
	int Next[maxn];

	void Get_Next(char* s) { //ACAM like KMP
		int len=strlen(s);
		Next[0]=-1;
		for(int i=1,j=-1; i<len; Next[i++]=j) {
			while(~j&&s[i]!=s[j+1]))j=Next[j];
			if(s[i]==s[j+1])j++;
		}
	}

	void solve(int x,int y,char* s,int &ans) {
		int lca=LCA(x,y),len=Depth[x]+Depth[y]-2*Depth[lca];
		int l=kth(x,Depth[x]-min(Depth[x],Depth[lca]+len-1)),r=kth(y,Depth[y]-min(Depth[y],Depth[lca]+len-1));
		Get_Next(s);
		int j=-1;
		for(; A!=lca; A=father[A]) {
			while(~j&&s[j+1]!=ch[A])j=Next[j];
			if(s[j+1]==ch[A])j++;
			if(j==len-1)ans++,j=Next[j];
		}
		static int tmp[maxl];
		int cnt=0;
		for(; B!=lca; B=father[B])tmp[++cnt]=tmp[ch[B]];
		for(; cnt; cnt--) {
			while(~j&&s[j+1]!=tmp[t])j=Next[j];
			if(s[j+1]==tmp[t])j++;
			if(j==len-1)ans++,j=Next[j];
		}
	}
} kmp;

struct Aho_Corasick_Automaton {
	struct Tree {

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
			int j=x;
			if(!ch(now,j))ch(now,j)=++cnt;
			now=ch(now,j);
		}
		return now;
	}
	
	void dfs(int Now) {
		Start[Now]=++step;
		for(int Next:edges[Now])dfs(Next);
		End[Now]=step;
	}

	void buildfail() {
		queue<int>Q;
		Q.push(root);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<26; i++) {
				int& next=ch(now,i);
				if(!next) {
					next=ch(fail(now),i)?ch(fail(now),i):root;
					continue;
				}
				Q.push(next);
				int p=fail(now);
				if(p)fail(next)=ch(p,i);
				else fail(next)=root;
			}
		}
		for(int i=2; i<=cnt; i++)AddEdge(fail(i),i);
		dfs(root);
	}
} acam;

void dfs(int Now,int acpos) {
	bit.add(acpos,1);
	for(auto x:q[Now]) {
		int id=x.id;
		if(x.bj>0)ans[x.id]+=bit.sum(x.pos);
		else ans[x.id]-=bit.sum(x.pos);
	}
	for(Edge &e:edges[Now])
		if(Next!=father[Now])dfs(Next,ac.child[pos][e.ch]);
	bit.add(acpos,-1);
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		char ch=' ';
		while(!isalpha(ch))ch=getchar();
		AddEdge(x,y,ch-'a');
		AddEdge(y,x,ch-'a');
	}
	Dfs(1);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		scanf("%s",s);
		int len=strlen(s);
		for(int j=0; j<len; j++)s[i]-='a';
		kmp.solve(x,y,s,ans);
		if(Depth[y]-Depth[lca]>=len) {
			int now=acam.insert(s);
			AddQuery(y,now,i,1);
			AddQuery(kth(y,Depth[y]-Depth[lca]-len+1),now,i,-1);
		}
		if(Depth[x]-Depth[lca]>=len) {
			reverse(s.begin(),s.end());
			int now=acam.insert(s);
			AddQuery(x,now,i,1);
			AddQuery(kth(x,Depth[x]-Depth[lca]-len+1),now,i,1);
		}
	}
	acam.buildfail();
	acam.dfs(1,1);
	for(int i=1; i<=m; i++)printf("%d\n",ans[i]);
	return 0;
} 
