#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=100005;

struct St {
	int u,v;
	St(int x=0,int y=0):u(x),v(y) {}
};

stack<St>S;
vector<int> edges[maxn],tree[maxn];

int n,m,step=0,Lowlink[maxn],Dfn[maxn],BCC=0,New,Square[maxn],Belong[maxn];

void AddEdge(int x,int y) {edges[x].push_back(y);}

void AddEdge2(int x,int y) {tree[x].push_back(y);}

void Tarjan(int Now,int fa) {
	step++;
	Lowlink[Now]=Dfn[Now]=step;
	for(int i=0; i<edges[Now].size(); i++) {
		int Next=edges[Now][i];
		if(!Dfn[Next]) {
			S.push(St(Now,Next));
			Tarjan(Next,Now);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
			if(Dfn[Now]<Lowlink[Next])AddEdge2(Now,Next),S.pop();
			else if(Dfn[Now]==Lowlink[Next]) {
				BCC++;
				AddEdge2(Now,++New);
				Square[New]=1;
				while(!S.empty()) {
					int u=S.top().u;
					S.pop();
					if(u==Now)break;
					Belong[u]=BCC;
					AddEdge2(New,u);
				}
			}
		} else if(Next!=fa&&Lowlink[Now]>Dfn[Next]) {
			Lowlink[Now]=Dfn[Next];
			S.push(St(Now,Next));
		}
	}
}

int f[maxn][2],g[maxn][2][2];

void TreeDp(int Now,int father) {
	if(Square[Now]) {
		for(int i=0; i<tree[Now].size(); i++) {
			int Next=tree[Now][i];
			TreeDp(Next,Now);
		}
		int Next=tree[Now][0];
		g[1][0][0]=g[1][0][1]=f[Next][0];
		g[1][1][0]=f[Next][1];
		g[1][1][1]=-0x7fffffff/2;
		for(int i=1; i<tree[Now].size(); i++) {
			int Next=tree[Now][i];
			if(i==tree[Now].size()-1) {
				g[i+1][1][0]=g[i][0][0]+f[Next][1];
				g[i+1][0][1]=max(g[i][0][1],g[i][1][1])+f[Next][0];
				g[i+1][0][0]=max(g[i][0][0],g[i][1][0])+f[Next][0];
			} else {
				for(int j=0; j<=1; j++) {
					g[i+1][1][j]=g[i][0][j]+f[Next][1];
					g[i+1][0][j]=max(g[i][0][j],g[i][1][j])+f[Next][0];
				}
			}
		}
		f[Now][1]=g[tree[Now].size()][0][1];
		f[Now][0]=max(g[tree[Now].size()][1][0],g[tree[Now].size()][0][0]);
	} else {
		f[Now][1]=1;
		for(int i=0; i<tree[Now].size(); i++) {
			int Next=tree[Now][i];
			TreeDp(Next,Now);
			if(!Square[Next]) {
				f[Now][1]+=f[Next][0];
				f[Now][0]+=max(f[Next][0],f[Next][1]);
			} else {
				f[Now][1]+=f[Next][1];
				f[Now][0]+=f[Next][0];
			}
		}
	}
}

int main() {
	New=n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	Tarjan(1,0);
	TreeDp(1,0);
	printf("%d\n",max(f[1][1],f[1][0]));
	return 0;
}