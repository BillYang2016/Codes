#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=200005;

vector<int> edges[maxn];
int n,Min[maxn],Max[maxn],sum=0;

void Dfs(int Now,int depth) {
	if(!edges[Now].size()) {sum++;Max[Now]=Min[Now]=1;return;}
	for(int Next:edges[Now])Dfs(Next,depth^1);
	if(!depth) { //先手
		Max[Now]=n;
		for(int Next:edges[Now]) {
			Max[Now]=min(Max[Now],Max[Next]);
			Min[Now]+=Min[Next];
		}
	} else {
		Min[Now]=n;
		for(int Next:edges[Now]) {
			Min[Now]=min(Min[Now],Min[Next]);
			Max[Now]+=Max[Next];
		}
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
	}
	Dfs(1,0);
	printf("%d %d\n",sum-Max[1]+1,Min[1]);
	return 0;
}