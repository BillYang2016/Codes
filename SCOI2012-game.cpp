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

typedef long long LL;

inline const LL Get_Int() {
	LL num=0,bj=1;
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

const int maxn=1605;
 
struct Edge {
	int from,to;
	LL cap,flow;
	Edge(int x=0,int y=0,LL c=0,LL f=0):from(x),to(y),cap(c),flow(f) {}
};
 
struct Dinic {
	int n,m,s,t;
	vector<Edge>edges;
	vector<int>G[maxn];
	bool vst[maxn];
	int dist[maxn],cur[maxn];
	void init(int n) {
		this->n=n;
		edges.clear();
		for(int i=1; i<=n; i++)G[i].clear();
	}
	void AddEdge(int x,int y,LL v) {
		edges.push_back(Edge(x,y,v,0));
		edges.push_back(Edge(y,x,0,0));
		m=edges.size();
		G[x].push_back(m-2);
		G[y].push_back(m-1);
	}
	bool bfs() {
		memset(vst,0,sizeof(vst));
		memset(dist,0,sizeof(dist));
		queue<int>Q;
		Q.push(t); //反向层次图
		vst[t]=1;
		while(!Q.empty()) {
			int Now=Q.front();
			Q.pop();
			for(int id:G[Now]) {
				Edge& e=edges[id^1];
				int Next=e.from;
				if(!vst[Next]&&e.cap>e.flow) { 
					vst[Next]=1;
					dist[Next]=dist[Now]+1;
					Q.push(Next);
				}
			}
		}
		return vst[s];
	}
	LL dfs(int Now,LL a) {
		if(Now==t||a==0)return a;
		LL flow=0;
		for(int& i=cur[Now]; i<G[Now].size(); i++) {
			Edge& e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Now]-1!=dist[Next])continue;
			LL nextflow=dfs(Next,min(a,e.cap-e.flow));
			if(nextflow>0) {
				e.flow+=nextflow;
				edges[G[Now][i]^1].flow-=nextflow;
				flow+=nextflow;
				a-=nextflow;
				if(a==0)break;
			}
		}
		return flow;
	}
	LL maxflow(int s,int t) {
		this->s=s;
		this->t=t;
		LL flow=0;
		while(bfs()) {
			memset(cur,0,sizeof(cur));
			flow+=dfs(s,LLONG_MAX);
		}
		return flow;
	}
} dinic;

const int Dirx[]= {0,1,-1,0,0},Diry[]= {0,0,0,1,-1};
int t,n,m,color[45][45];
LL a[45][45]; 

int id(int x,int y) {
	return (x-1)*m+y;
}

bool Check(LL Limit) {
	dinic.init(n*m+2);
	int S=n*m+1,T=n*m+2;
	LL sum=0;
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			if(color[i][j]) {
				dinic.AddEdge(S,id(i,j),Limit-a[i][j]);
				sum+=Limit-a[i][j];
				for(int k=1; k<=4; k++) {
					int nx=i+Dirx[k],ny=j+Diry[k];
					if(nx<1||ny<1||nx>n||ny>m)continue;
					dinic.AddEdge(id(i,j),id(nx,ny),LLONG_MAX/2);
				}
			} else dinic.AddEdge(id(i,j),T,Limit-a[i][j]);
		}
	return dinic.maxflow(S,T)==sum;
}

int main() {
	t=Get_Int();
	while(t--) {
		n=Get_Int();
		m=Get_Int();
		LL Max=0,sum1=0,sum2=0,num1=0,num2=0;
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++) {
				a[i][j]=Get_Int();
				color[i][j]=(i+j)&1;
				if(color[i][j])sum1+=a[i][j],num1++;
				else sum2+=a[i][j],num2++;
				Max=max(Max,a[i][j]);
			}
		if(num1!=num2) {
			LL x=(sum1-sum2)/(num1-num2);
			if(x>=Max&&Check(x))printf("%lld\n",x*num1-sum1);
			else puts("-1");
		} else {
			if(sum1!=sum2) {
				puts("-1");
				continue;
			}
			LL Left=Max,Right=LLONG_MAX/2;
			while(Left<=Right) {
				LL mid=(Left+Right)>>1;
				if(Check(mid))Right=mid-1;
				else Left=mid+1;
			}
			printf("%lld\n",Left*num1-sum1);
		}
	}
	return 0;
} 
