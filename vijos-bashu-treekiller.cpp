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

const int maxn=100005,maxb=325;

struct Edge {
	int from,to,dist;
};

int n,m,q,size,Upkey[maxn],Depth[maxn],Dist[maxn],Size[maxn],Key[maxn],p[maxn][25],Up[maxn][maxb],Jump[maxn][maxb],Remain[maxn][maxb];
vector<Edge>edges[maxn];

void AddEdge(int x,int y,int v) {
	edges[x].push_back((Edge) {x,y,v});
}

void Dfs(int Now,int fa,int depth,int dist,int last) {
	Depth[Now]=depth;
	Dist[Now]=dist;
	Size[Now]=1;
	p[Now][0]=fa;
	for(int i=1; i<=20; i++)
		if(~p[Now][i-1])p[Now][i]=p[p[Now][i-1]][i-1];
		else break;
	if(last)Up[Now][last]=fa;
	int pre=-1;
	for(int i=last+1; i<=min(size+1,dist); i++)Up[Now][i]=Up[fa][i-last];
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs(Next,Now,depth+1,dist+e.dist,e.dist);
		Size[Now]+=Size[Next];
	}
	if(depth%size==0&&Size[Now]>size)Key[Now]=1;
}

void Dfs2(int Now,int fa,int upkey) {
	if(upkey) {
		Upkey[Now]=upkey;
		for(int i=2; i<=size+1; i++)
			if(Dist[Now]-Dist[upkey]<=i) {
				Jump[Now][i]=1;
				Remain[Now][i]=i-(Dist[Now]-Dist[upkey]);
			} else if(~Up[Now][i]) {
				Jump[Now][i]=Jump[Up[Now][i]][i]+1;
				Remain[Now][i]=Remain[Up[Now][i]][i];
			} else {
				Jump[Now][i]=Jump[Up[Now][i-1]][i]+1;
				Remain[Now][i]=Remain[Up[Now][i-1]][i];
			}
	}
	for(Edge& e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs2(Next,Now,Key[Now]?Now:upkey);
	}
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	int k=20;
	for(int i=k; i>=0; i--) {
		if(Depth[a]==Depth[b])break;
		if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	}
	if(a==b)return b;
	for(int i=k; i>=0; i--)
		if(~p[a][i]&&p[a][i]!=p[b][i]) {
			a=p[a][i];
			b=p[b][i];
		}
	return p[a][0];
}

int Jump1(int Now,int target,int& remain,int step,int unused) {
	if(Now==target) {
		remain=unused;
		return 0;
	}
	if(Dist[Now]-Dist[target]<=unused) {
		remain=unused-(Dist[Now]-Dist[target]);
		return 0;
	}
	if((!unused||(unused==1&&Up[Now][1]==-1))&&Dist[Now]-Dist[target]<=step) {
		remain=step-(Dist[Now]-Dist[target]);
		return 1;
	}
	if(Depth[Upkey[Now]]<Depth[target]) {
		if(unused) {
			if(~Up[Now][unused])return Jump1(Up[Now][unused],target,remain,step,0);
			else if(unused>1)return Jump1(Up[Now][unused-1],target,remain,step,0);
		}
		if(~Up[Now][step])return Jump1(Up[Now][step],target,remain,step,0)+1;
		else return Jump1(Up[Now][step-1],target,remain,step,0)+1;
	}
	if(unused) {
		if(~Up[Now][unused])return Jump1(Up[Now][unused],target,remain,step,0);
		else if(unused>1)return Jump1(Up[Now][unused-1],target,remain,step,0);
	}
	return Jump1(Upkey[Now],target,remain,step,Remain[Now][step])+Jump[Now][step];
}

int Jump2(int Now,int target,int& remain,int step,int unused) {
	if(Now==target) {
		remain=unused;
		return 0;
	}
	if(Dist[Now]-Dist[target]<=unused) {
		remain=unused-(Dist[Now]-Dist[target]);
		return 0;
	}
	if((!unused||(unused==1&&Up[Now][1]==-1))&&Dist[Now]-Dist[target]<=step) {
		remain=step-(Dist[Now]-Dist[target]);
		return 1;
	}
	if(unused>=size) {
		if(~Up[Now][size])return Jump2(Up[Now][size],target,remain,step,unused-size);
		else return Jump2(Up[Now][size-1],target,remain,step,unused-size+1);
	} else if(unused) {
		if(~Up[Now][unused])return Jump2(Up[Now][unused],target,remain,step,0);
		else if(unused>1)return Jump2(Up[Now][unused-1],target,remain,step,1);
	}
	if(~Up[Now][size])return Jump2(Up[Now][size],target,remain,step,step-size)+1;
	else return Jump2(Up[Now][size-1],target,remain,step,step-size+1)+1;
}

int main() {
	memset(p,-1,sizeof(p));
	memset(Up,-1,sizeof(Up));
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	size=sqrt(n);
	Dfs(1,-1,1,0,0);
	Dfs2(1,-1,0);
	q=Get_Int();
	for(int i=1; i<=q; i++) {
		int s=Get_Int(),t=Get_Int(),v=Get_Int();
		int lca=LCA(s,t),ans=0,remain1=0,remain2=0;
		if(v>=size+1) {
			ans=Jump2(s,lca,remain1,v,0)+Jump2(t,lca,remain2,v,0);
			if(remain1&&remain2&&remain1+remain2>=v)ans--;
		} else {
			ans=Jump1(s,lca,remain1,v,0)+Jump1(t,lca,remain2,v,0);
			if(remain1&&remain2&&remain1+remain2>=v)ans--;
		}
		printf("%d\n",ans);
	}
	return 0;
}