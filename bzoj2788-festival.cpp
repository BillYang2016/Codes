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

vector<int>circle;

void Cal() {
	for(int x:circle)
		for(int y:circle)
			sum=max(map[x][y]);
	ans+=sum+1;
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
	if(Dfn[Now]==Dfn[Next]) {
		SCC++;
		circle.clear();
		int y;
		do {
			y=Stack[top--];
			Instack[y]=0;
			circle.push_back(y);
		} while(y!=Now);
		Cal();
	}
}

int main() {
	n=Get_Int();
	m1=Get_Int();
	m2=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			map[i][j]=i==j?0:INT_MAX/2;
	for(int i=1; i<=m1; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
		map[x][y]=min(map[x][y],1);
		map[y][x]=min(map[y][x],-1);
	}
	for(int i=1; i<=m2; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(y,x);
		map[y][x]=min(map[y][x],0);
	}
	for(int k=1; k<=n; k++)
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
	for(int i=1; i<n; i++)
		if(map[i][i]<0) {
			puts("NIE");
			return 0;
		}
	for(int i=1; i<=n; i++)
		if(!Dfn[i])Tarjan(i);
	printf("%d\n",ans);
	return 0;
} 
