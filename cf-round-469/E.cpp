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

int n,m,k,a[maxn],OutDegree[maxn],Size[maxn],Ans,Min=INT_MAX,step=0,top=0,SCC=0,Dfn[maxn],Lowlink[maxn],Stack[maxn],Belong[maxn];
bool Instack[maxn];
vector<int> edges[maxn],ans;

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
			Size[SCC]++;
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
		if((a[x]+1)%k==a[y])edges[x].push_back(y);
		if(a[x]==(a[y]+1)%k)edges[y].push_back(x);
	}
	for(int i=1; i<=(n<<1); i++)if(!Dfn[i])Tarjan(i);
	for(int Now=1; Now<=n; Now++)
		for(int Next:edges[Now])
			if(Belong[Now]!=Belong[Next])OutDegree[Belong[Now]]++;
	for(int i=1; i<=n; i++)if(!OutDegree[Belong[i]]&&Size[Belong[i]]<Min) {Min=Size[Belong[i]];Ans=Belong[i];}
	for(int i=1; i<=n; i++)if(Belong[i]==Ans)ans.push_back(i);
	printf("%d\n",ans.size());
	for(auto x:ans)printf("%d ",x);
	return 0;
}