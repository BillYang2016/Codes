#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=300005,maxc=26;

int n;

struct Suffix_Automaton {
	int cnt,root,last;
	int child[maxn<<1][maxc],next[maxn<<1],Max[maxn<<1];
	int buc[maxn<<1],top[maxn<<1],end_pos[maxn<<1],vst[maxn<<1];
	Suffix_Automaton() {init();}
	void init() {cnt=0;root=last=newnode(0);}
	int newnode(int val) {
		cnt++;
		next[cnt]=0;
		Max[cnt]=val;
		fill(child[cnt],child[cnt]+maxc,0);
		return cnt;
	}
	void insert(int data) {
		int p=last,u=newnode(Max[last]+1);
		end_pos[last=u]=1;
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
	void topsort() {
		for(int i=1; i<=cnt; i++)buc[Max[i]]++;
		for(int i=1; i<=cnt; i++)buc[i]+=buc[i-1];
		for(int i=1; i<=cnt; i++)top[buc[Max[i]]--]=i;
	}
	void get_end_pos() {
		topsort();
		for(int i=cnt; i>=1; i--)if(next[top[i]])end_pos[next[top[i]]]+=end_pos[top[i]];
	}
	int step;
	int run(string s) {
		int ans=0,len=0,p=root;step++;
		for(auto x:s) {
			int ch=x-'a';
			while(!child[p][ch]) {p=next[p];len=min(len,Max[p]);}
			!p?p=root,len=0:p=child[p][ch],len++;
			while(len>n&&Max[next[p]]>=n) {p=next[p];len=Max[p];}
			if(len>=n&&vst[p]!=step) {ans+=end_pos[p];len=Max[p];vst[p]=step;}
		}
		return ans;
	}
} sam;

char s[maxn];

int main() {
	scanf("%s",s);
	sam.build(s);
	sam.get_end_pos();
	int t=Get_Int();
	while(t--) {
		scanf("%s",s);
		n=strlen(s);
		copy(s,s+n,s+n);
		s[2*n]=0;
		printf("%d\n",sam.run(s));
	}
	return 0;
}