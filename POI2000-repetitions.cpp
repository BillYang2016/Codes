#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=2005,maxc=26;

int Min[maxn<<1];

struct Suffix_Automaton {
	int cnt,root,last;
	int child[maxn<<1][maxc],next[maxn<<1],Max[maxn<<1];
	int buc[maxn<<1],top[maxn<<1],tmp[maxn<<1];
	Suffix_Automaton() {root=last=newnode(0);}
	int newnode(int val) {Max[++cnt]=val;return cnt;}
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
				next[old]=next[u]=New;
				for(; child[p][data]==old; p=next[p])child[p][data]=New;
			}
		}
	}
	void build(string s) {for(char x:s)insert(x-'a');}
	void topsort() {
		for(int i=1; i<=cnt; i++)buc[Max[i]]++;
		for(int i=1; i<=cnt; i++)buc[i]+=buc[i-1];
		for(int i=1; i<=cnt; i++)top[buc[Max[i]]--]=i;
	}
	void lcs(string s) {
		memset(tmp,0,sizeof(tmp));
		int len=0,p=root;
		for(char x:s) {
			int ch=x-'a';
			if(child[p][ch])p=child[p][ch],len++;
			else {
				while(p&&!child[p][ch])p=next[p];
				if(!p)len=0,p=root;
				else len=Max[p]+1,p=child[p][ch];
			}
			tmp[p]=max(tmp[p],len);
		}
		for(int i=cnt; i>=1; i--) {
			int now=top[i];
			Min[now]=min(Min[now],tmp[now]);
			if(tmp[now]&&next[now])tmp[next[now]]=Max[next[now]];
		}
	}
} sam;

char s[maxn];

int main() {
	int n=Get_Int();
	scanf("%s",s);
	sam.build(s);
	sam.topsort();
	for(int i=1; i<=sam.cnt; i++)Min[i]=sam.Max[i];
	for(int i=1; i<n; i++) {
		scanf("%s",s);
		sam.lcs(s);
	}
	int ans=0;
	for(int i=1; i<=sam.cnt; i++)ans=max(ans,Min[i]);
	printf("%d\n",ans);
	return 0;
}