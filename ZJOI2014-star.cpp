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

const int maxn=100005,K=18;

struct Node {
	int n,x,y,x2,y2,xy;
	Node():Node(0,0) {n=0;}
	Node(int x,int y):n(1),x(x),y(y),x2(x*x),y2(y*y),xy(x*y) {}
	Node(int n,int x,int y,int x2,int y2,int xy):n(n),x(x),y(y),x2(x2),y2(y2),xy(xy) {}
	Node operator + (const Node& b) {return Node(n+b.n,x+b.x,y+b.y,x2+b.x2,y2+b.y2,xy+b.xy);}
	Node operator - (const Node& b) {return Node(n-b.n,x-b.x,y-b.y,x2-b.x2,y2-b.y2,xy-b.xy);}
	void operator += (const Node& b) {*this=*this+b;}
	double avg_x() {return 1.0*x/n;}
	double avg_y() {return 1.0*y/n;}
	double A() {return x2-2*avg_x()*x+n*avg_x()*avg_x();}
	double B() {return 2*avg_y()*x+2*avg_x()*y-2*xy-2*n*avg_x()*avg_y();}
	double C() {return y2-2*avg_y()*y+n*avg_y()*avg_y();}
	double delta() {
		if(n==1)return 0;
		double a=A(),b=B(),c=C(),d=sqrt(a*a+b*b+c*c-2*a*c);
		return (a+c-d)/2;
	}
} a[maxn];

int n,m,Depth[maxn],p[maxn][K];
vector<int> edges[maxn];

void AddEdge(int x,int y) {edges[x].push_back(y);}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)if(p[a][i]!=p[b][i])a=p[a][i],b=p[b][i];
	return p[a][0];
}

namespace Tree {
	void Dfs(int Now,int fa,int depth) {
		Depth[Now]=depth;
		p[Now][0]=fa;
		for(int i=1; i<K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
		for(int Next:edges[Now]) {
			if(Next==fa)continue;
			a[Next]+=a[Now];
			Dfs(Next,Now,depth+1);
		}
	}
	void solve() {
		Dfs(1,0,1);
		int q=Get_Int();
		while(q--) {
			int x=Get_Int(),y=Get_Int(),lca=LCA(x,y);
			printf("%0.5lf\n",(a[x]+a[y]-a[lca]-a[p[lca][0]]).delta());
		}
	}
}

namespace Circle {
	vector<int> cir;
	int step=0,top=0,Dfn[maxn],Lowlink[maxn],Stack[maxn],Color[maxn];
	bool inCircle[maxn];
	void Tarjan(int Now,int fa) {
		Dfn[Now]=Lowlink[Now]=++step;
		Stack[++top]=Now;
		for(int Next:edges[Now]) {
			if(Next==fa)continue;
			if(!Dfn[Next]) {
				Tarjan(Next,Now);
				Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
			} else Lowlink[Now]=min(Lowlink[Now],Dfn[Next]);
		}
		if(Dfn[Now]==Lowlink[Now]&&cir.empty()) {
			int y;
			do {
				y=Stack[top--];
				cir.push_back(y);
			} while(y!=Now);
			if(cir.size()>1)for(int x:cir)inCircle[x]=1;
			else cir.clear();
		}
	}
	void Dfs(int Now,int fa,int color,int depth) {
		Color[Now]=color;
		Depth[Now]=depth;
		p[Now][0]=fa;
		for(int i=1; i<K; i++)p[Now][i]=p[p[Now][i-1]][i-1];
		for(int Next:edges[Now]) {
			if(Next==fa||inCircle[Next])continue;
			a[Next]+=a[Now];
			Dfs(Next,Now,color,depth+1);
		}
	}
	int num[maxn];
	Node val[maxn<<1];
	void solve() {
		Tarjan(1,0);
		int cnt=0;
		for(int x:cir)Dfs(x,0,x,1),num[x]=++cnt;
		cir.insert(cir.end(),cir.begin(),cir.end());
		for(int i=0; i<cir.size(); i++)val[i+1]=val[i]+a[cir[i]];
		int q=Get_Int();
		while(q--) {
			int x=Get_Int(),y=Get_Int();
			if(Color[x]==Color[y]) {
				int lca=LCA(x,y);
				printf("%0.5lf\n",(a[x]+a[y]-a[lca]-a[p[lca][0]]).delta());
			} else {
				int fx=Color[x],fy=Color[y];
				Node tx=a[x]-a[fx],ty=a[y]-a[fy];
				if(num[fx]>num[fy])swap(fx,fy);
				Node cx=val[num[fy]]-val[num[fx]-1],cy=val[num[fx]+cnt]-val[num[fy]-1];
				printf("%0.5lf\n",min((tx+cx+ty).delta(),(tx+cy+ty).delta()));
			}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		int x=Get_Int(),y=Get_Int();
		a[i]=Node(x,y);
	}
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(x,y);
		AddEdge(y,x);
	}
	if(m==n-1)Tree::solve();
	else Circle::solve();
	return 0;
}