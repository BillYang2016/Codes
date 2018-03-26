#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=500005,maxc=2;

int n,len=0;
char s[maxn],ans[maxn];

struct Suffix_Automaton {
	int cnt,root,last;
	int child[maxn<<1][maxc],next[maxn<<1],Max[maxn<<1],father[maxn<<1];
	bool vst[maxn<<1],value[maxn<<1];
	Suffix_Automaton() {cnt=0;root=last=newnode(0);}
	int newnode(int val) {
		cnt++;
		Max[cnt]=val;
		return cnt;
	}
	void insert(int data) {
		int p=last,u=newnode(Max[last]+1);
		last=u;
		for(; p&&!child[p][data]; p=next[p])child[p][data]=u;
		if(!p)next[u]=root;
		else {
			int old=child[p][data];
			if(Max[old]==Max[p]+1)next[u]=old;
			else {
				int New=newnode(Max[p]+1);
				copy(child[old],child[old]+maxc,child[New]);
				next[New]=next[old];
				next[u]=next[old]=New;
				for(; child[p][data]==old; p=next[p])child[p][data]=New;
			}
		}
	}
	void build(string s) {for(auto x:s)insert(x-'a');}
	int bfs() {
		queue<int> Q;
		Q.push(root);
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			for(int i=0; i<maxc; i++) {
				int Next=child[Now][i];
				if(vst[Next])continue;
				vst[Next]=1;
				father[Next]=Now;
				value[Next]=i;
				if(!Next)return Next;
				Q.push(Next);
			}
		}
	}
	void dfs(int Now) {
		if(Now==root)return;
		dfs(father[Now]);
		ans[len++]='a'+value[Now];
	}
} sam;

int main() {
	n=Get_Int();
	scanf("%s",s);
	sam.build(s);
	sam.dfs(sam.bfs());
	printf("%d\n%s\n",len,ans);
	return 0;
}