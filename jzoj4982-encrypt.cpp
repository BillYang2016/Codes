#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=250005,maxc=26;

struct Suffix_Automaton {
	int cnt,root,last;
	int child[maxn<<1][maxc],next[maxn<<1],Max[maxn<<1];
	Suffix_Automaton() {cnt=0;root=last=newnode(0);}
	int newnode(int val) {Max[++cnt]=val;return cnt;}
	void insert(int data) {
		int p=last,u=newnode(Max[last]+1);
		last=u;
		f[u]=Len[u];
		for(; p&&!child[p][data]; p=next[p])child[p][data]=u;
		if(!p)next[u]=root;
		else {
			int old=child[p][data];
			if(Max[old]==Max[p]+1)next[u]=old;
			else {
				int New=newnode(Max[p]+1);
				f[New]=INT_MAX/2;
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
		for(int i=cnt; i>=1; i--)end_pos[next[top[i]]]=min(end_pos[next[top[i]]],end_pos[top[i]]);
	}
} sam;

int main() {
	scanf("%s",s+1);
	sam.build(s+1);
	sam.get_end_pos();
	int i=1;
	while(i<=n) {
		int j=i,now=1;
		while(j<=n&&sam.child[now][s[j]-'a']&&f[child[now][s[j]-'a']]<j)now=child[now][s[j++]-'a'];
		if(j==i)printf("-1 %d",s[i++]);
		else printf("%d %d",j-i,f[now]-(j-i)+1),i=j;
	}
	return 0;
}