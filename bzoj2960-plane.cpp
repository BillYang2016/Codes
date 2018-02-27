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

struct Point {
	int x,y;
} p[maxn];

struct Edge {
	int from,to,dist;
	int id,bj;
	double alpha;
	Edge() {from=to=dist=id=bj=alpha=0}
	Edge(int x,int y,int v):from(x),to(y),dist(v) {}
	Edge(int x,int y,int v,int num):from(x),to(y),dist(v),id(num),bj(0) {
		alpha=atan2(p[y].y-p[x].y,p[y].x-p[x].x);
	}
	bool operator < (const Edge& b) const {
		return alpha<b.alpha;
	}
} edges,a;

void Dfs(int Now,int id) {
	if(vst[Now])return;
	vst[Now]=1;
	edges[id].bj=id;
	Dfs(To[Now],id);
}

void build() {
	for(int i=1; i<=n; i++) {
		sort(Out[i].begin(),Out[i].end());
		int in=Out[i][0].id^1,out=Out.back().id;
		To[in]=out;
		for(int j=1; j<Out[i].size(); j++) {
			in=Out[i][j].id^1,out=Out[i][j-1].id;
			To[in]=out;
		}
	}
	n=m=0;
	for(int i=0; i<cnt; i++)
		if(!vst[i])Dfs(i,++n);
	for(int i=0; i<cnt; i++)
		if(edges[i].dist)a.push_back(Edge(edges[i].num,edges[i^1].num,edges[i].dist));
	for(int i=1; i<=n; i++)a.push_back(Edge(0,i,10000));
}

double Directed_MST(int n,vector<Edge>edges,int root) {
	double ans=0;
	static double in[maxn];
	static int id[maxn],pre[maxn],vst[maxn];
	while(true) {
		//找最小入边
		for(int i=1; i<=n; i++)in[i]=1e18;
		for(int i=0; i<edges.size(); i++) {
			Edge& e=edges[i]; 
			int x=e.from,y=e.to;
			if(x==y)continue;
			if(e.dist<in[y]) {
				pre[y]=x;
				in[y]=e.dist;
			}
		}
		for(int i=1; i<=n; i++) {
			if(i==root)continue;
			if(in[i]==1e18)return -1; //无解
		}
		//找环
		memset(id,0,sizeof(id));
		memset(vst,0,sizeof(vst));
		int cnt=0;
		in[root]=0;
		for(int i=1; i<=n; i++) {
			ans+=in[i];
			int now;
			for(now=i; vst[now]!=i&&!id[now]&&now!=root; now=pre[now])vst[now]=i; //找环
			if(now!=root&&!id[now]) { //缩点
				id[now]=++cnt;
				for(int p=pre[now]; p!=now; p=pre[p])id[p]=cnt;
			}
		}
		if(cnt==0)break; //无环
		for(int i=1; i<=n; i++)
			if(!id[i])id[i]=++cnt;
		for(int i=0; i<edges.size(); i++) {
			Edge& e=edges[i]; 
			int &x=e.from,&y=e.to;
			if(x!=y)e.dist-=in[y];
			x=id[x];
			y=id[y];
		}
		n=cnt;
		root=id[root];
	}
	return ans;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++) {
		p[i].x=Get_Int();
		p[i].y=Get_Int();
	}
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v1=Get_Int(),v2=Get_Int();
		edges.push_back(Edge(x,y,v1,cnt++));
		Out[x].push_back(edges.back());
		edges.push_back(Edge(y,x,v2,cnt++));
		Out[y].push_back(edges.back());
	}
	build();
	printf("%d\n",Directed_MST(n,a,0)-10000);
	return 0;
} 
