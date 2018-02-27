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

const int maxn=5005,maxm=305;

struct Simplex {
	int n,m;
	int a[maxn][maxm];
	void init(int m,int n) { //a矩阵m行n列 
		this->n=m;
		this->m=n;
	}
	void pivot(int in,int out) {
		for(int i=0; i<=m; i++) //重置out约束 
			if(i!=in)a[out][i]/=-a[out][in];
		a[out][in]=1/a[out][in];
		for(int i=0; i<=n; i++) { //重新计算其他约束 
			if(i==out||a[i][in]==0)continue;
			double t=a[i][in];
			a[i][in]=0;
			for(int j=0; j<=m; j++)a[i][j]+=t*a[out][j];
		}
	}
	int Solve() {
		while(true) {
			int in=0,out=0,Min=INT_MAX;
			for(int i=1; i<=m; i++)
				if(a[0][i]>0) {
					in=i;
					break;
				}
			if(!in)return a[0][0];
			for(int i=1; i<=n; i++)
				if(a[i][in]<0&&a[i][0]/-a[i][in]<Min) {
					Min=a[i][0]/-a[i][in];
					out=i;
				}
			if(!out)throw ; //unbounded
			pivot(in,out);
		}
	}
} fst;

vector<int>edges[305],in[305],out[305];
int n,id[305][305],cnt=0,rows=0,ans=0;
bool vst[305];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
	out[x].push_back(cnt);
	in[y].push_back(cnt);
}

void Dfs(int Now) {
	if(vst[Now])return;
	vst[Now]=1;
	if(Now!=1) {
		rows++;
		for(int pre:in[Now])fst.a[pre][rows]=-1;
		for(int suc:out[Now])fst.a[suc][rows]=1;
		fst.a[0][rows]=int(out[Now].size())-int(in[Now].size());
	}
	for(int Next:edges[Now])Dfs(Next);
}

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		int k=Get_Int();
		while(k--) {
			int x=Get_Int();
			id[x][i]=id[i][x]=++cnt;
			AddEdge(i,x);
			fst.a[cnt][0]=Get_Int();
			ans+=fst.a[cnt][0];
		}
	}
	Dfs(1);
	fst.init(cnt,rows);
	printf("%d\n",fst.Solve()+ans);
	return 0;
}