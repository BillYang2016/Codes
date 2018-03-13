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

int n,m,k,a[maxn],opp[maxn],step=0,top=0,SCC=0,Dfn[maxn],Lowlink[maxn],Stack[maxn],Belong[maxn];
bool Instack[maxn],vst[maxn];
vector<int> edges[maxn];

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
		int y;
		SCC++;
		do {
			y=Stack[top--];
			Instack[y]=0;
			Belong[y]=SCC;
		} while(y!=Now);
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		if(a[x]==a[y]) {
			edges[x].push_back(n+y);
			edges[y].push_back(n+x);
			edges[n+x].push_back(y);
			edges[n+y].push_back(x);
		} else if((a[x]+1)%k==a[y]) {
			edges[n+x].push_back(n+y);
			edges[y].push_back(x);
		} else if((a[y]+1)%k==a[x]) {
			edges[n+y].push_back(n+x);
			edges[x].push_back(y);
		}
	}
	for(int i=1; i<=(n<<1); i++)if(!Dfn[i])Tarjan(i);
	for(int i=1; i<=n; i++) {
		opp[Belong[i]]=Belong[n+i];
		opp[Belong[n+i]]=Belong[i];
	}
	for(int i=1; i<=SCC; i++)if(!vst[i])vst[opp[i]]=1;
	for(int i=1; i<=(n<<1); i++)if(!vst[Belong[i]])printf("%d ",i);
	return 0;
}