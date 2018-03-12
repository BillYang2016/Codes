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
using FastIO::Get_Int;

const int maxn=5005;
const double eps=1e-4;

struct Edge {
	int from,to,dist;
};

double dist[maxn];
int n,m,cnt[maxn];
bool inque[maxn];
vector<Edge> edges[maxn];

void AddEdge(int x,int y,int v) {
	edges[x].push_back((Edge) {x,y,v});
}

bool Spfa(double mid) {
	stack<int> Q;
	for(int i=1; i<=n; i++) {
		dist[i]=cnt[i]=0;
		inque[i]=1;
		Q.push(i);
	}
	while(!Q.empty()) {
		int Now=Q.top();
		Q.pop();
		inque[Now]=0;
		for(Edge &e:edges[Now]) {
			int Next=e.to;
			if(dist[Now]+e.dist+mid<dist[Next]) {
				dist[Next]=dist[Now]+e.dist+mid;
				if(++cnt[Next]>=n)return 1;
				if(!inque[Next]) {inque[Next]=1;Q.push(Next);}
			}
		}
	}
	return 0;
}

int main() {
	n=Get_Int()+2;
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),a=Get_Int(),b=Get_Int(),c=Get_Int(),d=Get_Int();
		AddEdge(x,y,b+d);
		if(c)AddEdge(y,x,a-d);
	}
	double Left=0,Right=1e9;
	while(Right-Left>eps) {
		double mid=(Left+Right)/2;
		if(Spfa(mid))Left=mid;
		else Right=mid;
	}
	printf("%0.2lf\n",(Left+Right)/2);
	return 0;
}