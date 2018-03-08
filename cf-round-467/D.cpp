#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005,maxs=1000005;

int n,s,size,bj,times=0,ans[maxs];
bool vst[maxn][2];
vector<int> edges[maxn];

void Dfs(int Now,int depth) {
	if(bj==1)return;
	ans[depth]=Now;
	vst[Now][depth&1]=1;
	for(int Next:edges[Now]) {
		if(vst[Next][(depth&1)^1])continue;
		Dfs(Next,depth+1);
	}
	if((depth&1)&&!edges[Now].size()) {size=depth;bj=1;return;}
	if(!(depth&1)&&!bj) {bj=2;return;}
}

int main() {
	n=Get_Int();
	Get_Int();
	for(int i=1; i<=n; i++) {
		int num=Get_Int();
		for(int j=1; j<=num; j++) {
			int x=Get_Int();
			edges[i].push_back(x);
		}
	}
	queue<int> Q;
	Q.push(s=Get_Int());
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		for(int Next:edges[Now])Q.push(Next),times++;
		if(times>=1000000) {
			bj=3;
			break;
		}
	}
	Dfs(s,0);
	if(bj==1) {
		puts("Win");
		for(int i=0; i<=size; i++)printf("%d ",ans[i]);
		putchar('\n');
	} else puts(bj==2?"Lose":"Draw");
	return 0;
}