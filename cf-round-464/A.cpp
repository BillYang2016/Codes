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

const int maxn=5005;

int n,step=0,top=0,Dfn[maxn],Lowlink[maxn],Stack[maxn];
bool Instack[maxn],bj=0;
vector<int> edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Tarjan(int Now) {
	Dfn[Now]=Lowlink[Now]=++step;
	Stack[++top]=Now;
	Instack[Now]=1;
	for(int Next:edges[Now]) {
		if(!Dfn[Next]) {
			Tarjan(Next);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
		} else if(Instack[Next])Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
	}
	if(Dfn[Now]==Lowlink[Now]) {
		int y,size=0;
		do {
			y=Stack[top--];
			Instack[y]=0;
			size++;
		} while(y!=Now);
		if(size==3)bj=1;
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)AddEdge(i,Get_Int());
	for(int i=1; i<=n; i++)if(!Dfn[i])Tarjan(i);
	puts(bj?"YES":"NO");
	return 0;
}