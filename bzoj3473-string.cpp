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

const int maxn=100005,maxc=26;

int n,k;

struct SuffixAutomaton {
	int cnt,root,last;
	int next[maxn*2],Max[maxn*2],Times[maxn*2],Last[maxn*2],Ans[maxn*2];
	int child[maxn*2][maxc];
	SuffixAutomaton() {
		cnt=0;
		root=last=newnode(0);
	}
	int newnode(int val) {
		cnt++;
		next[cnt]=Times[cnt]=0;
		Max[cnt]=val;
		memset(child[cnt],0,sizeof(child[cnt]));
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
	void build(string s) {
		last=root;
		for(auto x:s)insert(x-'a');
	}
	int run(string s,int id) {
		int now=root;
		for(auto x:s) {
			int ch=x-'a';
			now=child[now][ch];
			int p=now; 
			while(Last[p]!=id) {
				Times[p]++;
				Last[p]=id;
				p=next[p];
			}
		}
	}
	vector<int>edges[maxn*2];
	void buildtree() {
		for(int i=2; i<=cnt; i++)edges[next[i]].push_back(i);
	}
	void dp(int now) {
		if(Times[now]>=k)Ans[now]+=Max[now]-Max[next[now]];
		for(int Next:edges[now]) {
			Ans[Next]+=Ans[now];
			dp(Next);
		}
	}
	int cal(string s) {
		int now=root,ans=0;
		for(auto x:s) {
			int ch=x-'a';
			now=child[now][ch];
			ans+=Ans[now];
		}
		return ans;
	}
} sam;

string s[maxn];

int main() {
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=1; i<=n; i++) {
		cin>>s[i];
		sam.build(s[i]);
	}
	for(int i=1; i<=n; i++)sam.run(s[i],i);
	sam.buildtree();
	sam.dp(sam.root);
	for(int i=1; i<=n; i++)printf("%d ",sam.cal(s[i]));
	return 0;
}