#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
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

const int maxn=250005,maxc=10;
int Bucket[maxn*2],top[maxn*2],tmp[maxn*2],Min[maxn*2];

struct SuffixAutomaton {
	int cnt,root,last;
	int next[maxn*2],Max[maxn*2],end_pos[maxn*2];
	int child[maxn*2][maxc];
	SuffixAutomaton() {
		cnt=0;
		root=last=newnode(0);
	}
	int newnode(int val) {
		cnt++;
		next[cnt]=end_pos[cnt]=0;
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
	void build(vector<int> a) {
		for(auto x:a)insert(x);
	}
	void topsort() {
		for(int i=1; i<=cnt; i++)Bucket[Max[i]]++;
		for(int i=1; i<=cnt; i++)Bucket[i]+=Bucket[i-1];
		for(int i=1; i<=cnt; i++)top[Bucket[Max[i]]--]=i;
	}
	void lcs(vector<int> a) {
		memset(tmp,0,sizeof(tmp));
		int len=0,p=root;
		for(auto ch:a) {
			if(child[p][ch])p=child[p][ch],len++;
			else {
				while(p&&!child[p][ch])p=next[p];
				if(!p) {
					len=0;
					p=root;
				} else {
					len=Max[p]+1;
					p=child[p][ch];
				}
			}
			tmp[p]=max(tmp[p],len);
		}
		for(int i=cnt; i>=1; i--) { //逆拓扑序 
			int Now=top[i];
			Min[Now]=min(Min[Now],tmp[Now]);
			if(tmp[Now]&&next[Now])tmp[next[Now]]=Max[next[Now]];
		}
	}
} sam;

int main() {
	t=Get_Int();
	int l=Get_Int();
	for(int i=1; i<=l; i++)a.push_back(Get_Int());
	sam.build(a);
	for(int i=1; i<=sam.cnt; i++)Min[i]=sam.Max[i];
	sam.topsort();
	for(int i=1; i<t; i++) {
		int l=Get_Int();
		a.clear();
		for(int i=1; i<=l; i++)a.push_back(Get_Int());
		sam.lcs(a);
	}
	int ans=0;
	for(int i=1; i<=sam.cnt; i++)ans=max(ans,Min[i]);
	printf("%d\n",ans);
	return 0;
}