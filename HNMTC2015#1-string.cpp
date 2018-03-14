#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct Palindsome_Automaton {
	int child[maxn][26];
	int n,size,last,s[maxn],len[maxn],next[maxn],fa[maxn],half[maxn],f[maxn];
	Palindsome_Automaton() {init();}
	void init() {
		size=-1;
		newnode(0); //even
		newnode(-1); //odd
		last=n=0;
		s[0]=-1;
		next[0]=next[1]=1;
	}
	int newnode(int v) {
		int now=++size;
		memset(child[now],0,sizeof(child[now]));
		next[now]=0;
		len[now]=v;
		return now;
	}
	void insert(int data) {
		s[++n]=data;
		int p=last;
		while(s[n-len[p]-1]!=s[n])p=next[p];
		if(!child[p][data]) {
			int now=newnode(len[p]+2),q=next[p];
			while(s[n-len[q]-1]!=s[n])q=next[q];
			next[now]=child[q][data];
			q=half[p];
			while(s[n-len[q]-1]!=s[n]||len[child[q][data]]*2>len[now])q=next[q];
			half[now]=child[q][data];
			child[p][data]=now;fa[now]=p;
		}
		last=child[p][data];
	}
	void build(string s) {for(auto x:s)insert(x-'a');}
	void dp() {
		for(int i=2; i<=size; i++)f[i]=INT_MAX/2;
		f[0]=1;
		int ans=n;
		for(int i=1; i<=size; i++) {
			if(!(len[i]&1))f[i]=min(f[fa[i]]+1,f[half[i]]+len[i]/2-len[half[i]]+1);
			ans=min(ans,n-len[i]+f[i]);
		}
		printf("%d\n",ans);
	}
} pam;

char s[maxn];

int main() {
	int t=Get_Int();
	while(t--) {
		pam.init();
		scanf("%s",s+1);
		pam.build(s+1);
		pam.dp();
	}
	return 0;
}