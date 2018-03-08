#include<bits/stdc++.h>

using namespace std;

namespace FastIO {
	const int L=1<<15;
	char buf[L],*S,*T;
	char getchar() {
		if(S==T) {T=(S=buf)+fread(buf,1,L,stdin);if(S==T)return EOF;}
		return *S++;
	}
	int Get_Int() {
		int res=0,bj=1;char c=getchar();
		while(!isdigit(c)) {if(c=='-')bj=-1;c=getchar();}
		while(isdigit(c)) {res=res*10+c-'0';c=getchar();}
		return res*bj;
	}
}

using namespace FastIO;

const int maxn=1000005;

int n,m,k,step=0,top=0,BCC=0,Dfn[maxn<<2],Lowlink[maxn<<2],Stack[maxn<<2],Belong[maxn<<2];
bool Instack[maxn<<2];
vector<int> edges[maxn<<2];

void AddEdge(int x,int y) {edges[x].push_back(y);}

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
		BCC++;
		int y;
		do {
			y=Stack[top--];
			Instack[y]=0;
			Belong[y]=BCC;
		} while(y!=Now);
	}
}

bool Check() {
	for(int i=0; i<(n<<2); i++)if(!Dfn[i])Tarjan(i);
	for(int i=0; i<(n<<2); i+=2)if(Belong[i]==Belong[i^1])return false;
	return true;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int()-1,y=Get_Int()-1;
		AddEdge(x<<1,y<<1|1);
		AddEdge(y<<1,x<<1|1);
	}
	for(int i=0; i<n; i++) {
		AddEdge(i<<1|1,n+i<<1|1);
		AddEdge(n+i<<1,i<<1);
	}
	for(int i=1; i<=k; i++) {
		int num=Get_Int(),last;
		for(int j=1; j<=num; j++) {
			int x=Get_Int()-1;
			if(j>1) {
				AddEdge(n+x<<1,n+last<<1);
				AddEdge(n+last<<1|1,n+x<<1|1);
				AddEdge(x<<1|1,n+last<<1);
				AddEdge(n+last<<1|1,x<<1);
			}
			last=x;
		}
	}
	puts(Check()?"TAK":"NIE");
	return 0;
}