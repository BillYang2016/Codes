#include<bits/stdc++.h>

using namespace std;

const int maxn=1000005,maxc=26;

struct Suffix_Automaton {
	int cnt,root,last,f;
	int child[maxn<<1][maxc],next[maxn<<1],Max[maxn<<1];
	Suffix_Automaton() {init();}
	void init() {cnt=f=0;root=last=newnode(0);}
	int newnode(int val) {
		cnt++;
		next[cnt]=0;
		Max[cnt]=val;
		fill(child[cnt],child[cnt]+maxc,0);
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
			f=max(f,Max[next[u]]);
		}
	}
} sam;

string s;

int main() {
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--) {
		cin>>s;
		sam.init();
		char last=s[0];
		bool flag=0;
		for(auto x:s) {
			sam.insert(x-'a');
			if(x!=last)flag=1;
			printf("%d ",flag?sam.f+1:0);
		}
		putchar('\n');
	}
	return 0;
}