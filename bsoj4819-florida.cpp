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

void Kruskal() {
	int id=0;
	sort(edges.begin(),edges.end());
	for(auto e:edges) {
		int fx=Get_Father(e.from),fy=Get_Father(e.to);
		if(fx!=fy) {
			father[fx]=fy;
			S.push_back(id);
			AddEdge(e.from,e.to);
			AddEdge(e.to,e.from);
		}
		id++;
	}
}

void Dfs(int Now,int father) {
	for(int Next:edges[Now]) {
		if(Next==father)continue;
		color[Next]=color[Now]^1;
		Dfs(Next,Now);
	}
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
		SCC++;
		int y;
		do {
			y=Stack[top--];
			Instack[y]=0;
			Belong[y]=SCC;
		} while(y!=Now);
	}
}

bool Check(int A,int B) {
	step=SCC=0;
	for(int i=1; i<=2*n; i++) {
		edges[i].clear();
		Dfn[i]=0;
	}
	for(int i=1; i<n; i++)
		for(int j=i+1; j<=n; j++) {
			if(map[i][j]<=A)continue;
			else if(map[i][j]<=B) {
				AddEdge(i,n+j);
				AddEdge(j,n+i);
			} else {
				AddEdge(i,n+j);
				AddEdge(n+j,i);
				AddEdge(n+i,j);
				AddEdge(j,n+i);
			}
		}
	for(int i=1; i<=2*n; i++)if(!Dfn[i])Tarjan(i);
	for(int i=1; i<=n; i++)if(Belong[i]==Belong[n+i])return false;
	return true;
}

int main() {
	while(scanf("%d",&n)) {
		for(int i=1; i<n; i++)
			for(int j=i+1; j<=n; j++) {
				map[i][j]=Get_Int();
				edge.push_back((Edge) {i,j,map[i][j]});
			}
		for(int i=1; i<=n; i++) {
			father[i]=i;
			edges[i].clear();
		}
		Kruskal();
		color[1]=0;
		Dfs(1,0);
		for(int i=1; i<=n; i++)
			for(int j=i+1; j<=n; j++)
				if(color[i]==color[j]) { //特判二分图
					if(!color[i])Max0=max(Max0,map[i][j]);
					else Max1=max(Max1,map[i][j]);
				}
		ans=Max0+Max1;
		for(auto id:S) {
			int Left=id,Right=edge.size()-1,B=edges[id].dist;
			if(B>ans)break;
			while(Left<=Right) {
				int mid=(Left+Right)>>1,A=edges[mid].dist;
				if(Check(A,B))Left=mid+1;
				else Right=mid-1;
			}
			ans=min(ans,edges[Right].dist+B);
		}
	}
	return 0;
} 
