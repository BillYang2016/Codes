#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=25,maxs=1<<20;

int n,m,q;
vector<int> edges[maxn],edges_s[maxs];

void Dfs(int Now) {
	vst[Now]=1;
	S.push(Now);
	for(int Next:edges_s[Now]) {
		if(vst[Next]) {
			Found=1;
			while(!S.empty()&&S.top()!=Next) {Circle[S.top()]=1;S.pop();}
			Circle[Next]=1;
		}
		if(!Found)Dfs(Next);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	int Start=1;
	for(int i=1; i<=n; i++)if(Get_Int())Start|=1<<(i-1);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[y].push_back(x);
	}
	for(int S=0; S<(1<<n); S++) {
		int T=0;
		for(int i=1; i<=n; i++) {
			int cnt=0;
			for(int j:edges[i])cnt+=S>>j&1;
			if(cnt&1)T|=1<<(i-1);
		}
		edges_s[S].push_back(T);
	}
	Dfs(Start);
	return 0;
}