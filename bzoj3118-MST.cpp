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

const int maxn=1005,maxm=4005;
const double eps=1e-6;

int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}

struct Simplex {
	int n,m;
	double a[maxn][maxm];
	void init(int m,int n) { //a矩阵m行n列 
		this->n=m;
		this->m=n;
	}
	void pivot(int in,int out) {
		for(int i=0; i<=m; i++) //重置out约束 
			if(i!=in)a[out][i]/=-a[out][in];
		a[out][in]=1/a[out][in];
		for(int i=0; i<=n; i++) { //重新计算其他约束 
			if(i==out||dcmp(a[i][in])==0)continue;
			double t=a[i][in];
			a[i][in]=0;
			for(int j=0; j<=m; j++)a[i][j]+=t*a[out][j];
		}
	}
	double Solve() {
		while(true) {
			int in=0,out=0;
			double Min=1e18;
			for(int i=1; i<=m; i++)
				if(dcmp(a[0][i])>0) {
					in=i;
					break;
				}
			if(!in)return a[0][0];
			for(int i=1; i<=n; i++)
				if(dcmp(a[i][in])<0&&a[i][0]/-a[i][in]<Min) {
					Min=a[i][0]/-a[i][in];
					out=i;
				}
			if(!out)throw ; //unbounded
			pivot(in,out);
		}
	}
} fst;

struct Edge {
	int from,to,dist;
};

vector<Edge>edges[305];
int n,m,Depth[305],c[maxn],x[maxn],y[maxn],w[maxn],bj[maxn],father[305],id[305][305],rows=0;

void AddEdge(int x,int y,int v) {
	edges[x].push_back((Edge) {x,y,v});
}

void Dfs(int Now,int fa,int depth) {
	father[Now]=fa;
	Depth[Now]=depth;
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1);
	}
}

void AddRestrain(int tree,int nottree) {
	rows++;
	fst.a[tree][rows]=-1;
	fst.a[nottree][rows]=-1;
	fst.a[0][rows]=w[tree]-w[nottree];
}

void Jump(int x,int y,int _id) {
	if(Depth[x]<Depth[y])swap(x,y);
	while(Depth[x]>Depth[y]) {
		AddRestrain(id[x][father[x]],_id);
		x=father[x];
	}
	if(x==y)return;
	while(x!=y) {
		AddRestrain(id[x][father[x]],_id);
		AddRestrain(id[y][father[y]],_id);
		x=father[x];
		y=father[y];
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		x[i]=Get_Int();
		y[i]=Get_Int();
		w[i]=Get_Int();
		bj[i]=Get_Int();
		int inc=Get_Int(),dec=Get_Int();
		if(bj[i]) {
			c[i]=dec;
			id[x[i]][y[i]]=id[y[i]][x[i]]=i;
			AddEdge(x[i],y[i],w[i]);
			AddEdge(y[i],x[i],w[i]);
		} else c[i]=inc;
	}
	Dfs(1,-1,1);
	for(int i=1; i<=m; i++)fst.a[i][0]=c[i];
	for(int i=1; i<=m; i++)
		if(!bj[i])Jump(x[i],y[i],i);
	fst.init(m,rows);
	printf("%d\n",int(fst.Solve()));
	return 0;
}