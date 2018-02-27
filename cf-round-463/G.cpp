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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=1000005,mod=1e9+7;

struct Palindsome_Automaton {
	int child[maxn][26];
	int n,size,last,s[maxn],len[maxn],next[maxn],diff[maxn],snext[maxn];
	Palindsome_Automaton() {
		size=-1;
		newnode(0); //even
		newnode(-1); //odd
		last=n=0;
		s[0]=-1;
		next[0]=next[1]=1;
	}
	int newnode(int v) {
		int now=++size;
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
			child[p][data]=now;
			diff[now]=len[now]-len[next[now]];
			snext[now]=diff[now]==diff[next[now]]?snext[next[now]]:next[now];
		}
		last=child[p][data];
	}
} pam;

char s[maxn],tmp[maxn];
int n;
int f[maxn],series[maxn];

void add(int &x,int v) {
	x+=v;
	if(x>=mod)x-=mod;
}

int main() {
	scanf("%s",tmp+1);
	n=strlen(tmp+1);
	for(int i=1; i<=(n>>1); i++)s[(i<<1)-1]=tmp[i];
	for(int i=1; i<=(n>>1); i++)s[i<<1]=tmp[n-i+1];
	f[0]=1;
	for(int i=1; i<=n; i++) {
		pam.insert(s[i]-'a');
		for(int v=pam.last; pam.len[v]>0; v=pam.snext[v]) {
			series[v]=f[i-(pam.len[pam.snext[v]]+pam.diff[v])];
			if(pam.diff[v]==pam.diff[pam.next[v]])add(series[v],series[pam.next[v]]);
			add(f[i],series[v]);
		}
		if(i&1)f[i]=0;
	}
	printf("%d\n",f[n]);
	return 0;
}