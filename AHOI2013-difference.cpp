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

typedef long long LL;

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

const int maxn=500005,maxc=26;

int n;

struct SuffixAutomaton {
	int cnt,root,last;
	int next[maxn*2],Max[maxn*2],end_pos[maxn*2],Bucket[maxn*2],top[maxn*2];
	int child[maxn*2][maxc];
	SuffixAutomaton() {
		cnt=0;
		root=last=newnode(0);
	}
	int newnode(int val) {
		cnt++;
		next[cnt]=0;
		Max[cnt]=val;
		memset(child[cnt],0,sizeof(child[cnt]));
		return cnt;
	}
	void insert(int data) {
		int p=last,u=newnode(Max[last]+1);
		last=u;
		end_pos[u]=1;
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
	void build(string s) {
		for(auto x:s)insert(x-'a');
	}
	void topsort() {
		for(int i=1; i<=cnt; i++)Bucket[Max[i]]++;
		for(int i=1; i<=cnt; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=cnt; i++)top[Bucket[Max[i]]--]=i;
	}
	LL dp() {
		LL ans=(LL)(n-1)*n*(n+1)/2;
		for(int i=cnt; i>=1; i--) {
			int now=top[i],fa=next[now];
			ans-=2ll*end_pos[now]*end_pos[fa]*Max[fa];
			if(fa)end_pos[fa]+=end_pos[now];
		}
		return ans;
	}
} sam;

char s[maxn];

int main() {
	scanf("%s",s);
	n=strlen(s);
	reverse(s,s+n);
	sam.build(s);
	sam.topsort();
	printf("%lld\n",sam.dp());
	return 0;
}