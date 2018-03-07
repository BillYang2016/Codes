#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=3005;
const double eps=1e-6;

int dcmp(double x) {
	if(fabs(x)<=eps)return 0;
	return x>eps?1:-1;
}

struct Edge {
	int from,to;
	double cap,flow;
	Edge(int x=0,int y=0,double c=0,double f=0):from(x),to(y),cap(c),flow(f) {}
};

struct Dinic {
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn];
	bool vst[maxn];
	int dist[maxn],cur[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,double v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bfs() {
		fill(vst+1,vst+n+1,0);
		queue<int> Q;
		Q.push(t);
		vst[t]=1;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			for(int id:G[Now]) {
				Edge& e=edges[id^1];
				int Next=e.from;
				if(!vst[Next]&&dcmp(e.cap-e.flow)>0) { 
					vst[Next]=1;
					dist[Next]=dist[Now]+1;
					if(Next==s)return 1;
					Q.push(Next);
				}
			}
		}
		return vst[s];
	}
	double dfs(int Now,double a) {
		if(Now==t||dcmp(a)==0)return a;
		double flow=0;
		for(int &i=cur[Now]; i<G[Now].size(); i++) {
			int id=G[Now][i];
			Edge &e=edges[id];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			double nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(dcmp(nextflow)>0) {
				e.flow+=nextflow;
				edges[id^1].flow-=nextflow;
				flow+=nextflow;
				a-=nextflow;
				if(a==0)break;
			}
		}
		return flow;
	}
	double maxflow(int s,int t) {
		this->s=s;
		this->t=t;
		double flow=0;
		while(bfs()) {
			memset(cur,0,sizeof(cur));
			flow+=dfs(s,1e18);
		}
		return flow;
	}
} dinic;

struct Cheese {
	int p,x,y;
} a[maxn];

int n,m,v[maxn],sum=0;
double Time[maxn];

bool Check(double t) {
	int S=n+n*m*2+1,T=n+n*m*2+2;
	dinic.init(T);
	for(int i=1; i<=n; i++) {
		dinic.AddEdge(S,i,a[i].p);
		Time[i]=a[i].x;
		Time[n+i]=a[i].y+t;
	}
	sort(Time+1,Time+2*n+1);
	for(int i=2; i<=2*n; i++) {
		double x=Time[i]-Time[i-1];
		if(x<eps)continue;
		for(int j=1; j<=m; j++) {
			int y=n+(i-1)*m+j;
			dinic.AddEdge(y,T,j*v[j]*x);
			for(int k=1; k<=n; k++)
				if(dcmp(Time[i-1]-a[k].x)>=0&&dcmp(Time[i]-a[k].y-t)<=0)dinic.AddEdge(k,y,v[j]*x);
		}
	}
	return dcmp(dinic.maxflow(S,T)-sum)>=0;
}

int main() {
	int t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		sum=0;
		for(int i=1; i<=n; i++) {
			a[i].p=Get_Int();
			a[i].x=Get_Int();
			a[i].y=Get_Int();
			sum+=a[i].p;
		}
		for(int i=1; i<=m; i++)v[i]=Get_Int();
		double Left=0,Right=sum/v[1]+1;
		sort(v+1,v+m+1,greater<int>());
		for(int i=1; i<m; i++)v[i]-=v[i+1];
		while(Right-Left>eps) {
			double mid=(Left+Right)/2;
			if(Check(mid))Right=mid;
			else Left=mid;
		}
		printf("%0.4lf\n",(Left+Right)/2);
	}
	return 0;
}