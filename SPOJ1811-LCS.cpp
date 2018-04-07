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
	int run(string s) {
		int p=root,len=0,ans=0;
		for(auto x:s) {
			int ch=x-'a';
			if(child[p][ch])len++,p=child[p][ch];
			else {
				while(p&&!child[p][ch])p=next[p];
				if(!p)len=0,p=root;
				else len=Max[p]+1,p=child[p][ch];
			}
			ans=max(ans,len);
		}
		return ans;
	}
} sam;

char A[maxn],B[maxn];

int main() {
	scanf("%s%s",A,B);
	sam.build(A);
	printf("%d\n",sam.run(B));
	return 0;
}