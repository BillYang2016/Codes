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

int step=0,Lowlink[maxn],Dfn[maxn],BCC=0,New,Square[maxn],Length[maxn],f[maxn],Belong[maxn];

vector<int>edges[maxn];

struct Edge {
	int from,to,dist;
	Edge(int x=0,int y=0,int v=0):from(x),to(y),dist(v) {}
};

vector<Edge>tree[maxn];

struct St {
	int u,v;
	St(int _u=0,int _v=0):u(_u),v(_v) {}
};

stack<St>S;

void AddEdge(int x,int y) {edges[x].push_back(y);}

void AddEdge(int x,int y,int v) {tree[x].push_back(Edge(x,y,v));}

vector<int>Circle[maxn];

void Tarjan(int Now,int fa) {
	step++;
	Lowlink[Now]=Dfn[Now]=step;
	for(int i=0; i<edges[Now].size(); i++) {
		int Next=edges[Now][i];
		if(!Dfn[Next]) {
			S.push(St(Now,Next));
			Tarjan(Next,Now);
			Lowlink[Now]=min(Lowlink[Now],Lowlink[Next]);
			if(Dfn[Now]<Lowlink[Next])AddEdge(Now,Next,1),S.pop();
			else if(Dfn[Now]==Lowlink[Next]) { //构成点双连通分量
				BCC++;
				AddEdge(Now,++New,0);
				Square[New]=1;
				while(!S.empty()) {
					int u=S.top().u,v=S.top().v;
					S.pop();
					Length[BCC]++;
					f[u]=f[v]+1;
					if(u!=Now) {
						Belong[u]=BCC;
						Circle[New].push_back(u);
					}
					if(u==Now&&v==Next)break;
				}
				for(int i=0; i<Circle[New].size(); i++) {
					int Next=Circle[New][i];
					AddEdge(New,Next,min(abs(f[Next]-f[Now]),Length[BCC]-abs(f[Next]-f[Now])));
				}
			}
		} else if(Next!=fa&&Lowlink[Now]>Dfn[Next]) {
			Lowlink[Now]=Dfn[Next];
			S.push(St(Now,Next));
		}
	}
}

int n,m,Dist1[maxn],Dist2[maxn],a[maxn],ans=0;

void TreeDp(int Now) {
	for(Edge& e:tree[Now]) {
		int Next=e.to;
		TreeDp(Next);
		if(Dist1[Next]+e.dist>Dist1[Now]) { //所有转移都一样
			Dist2[Now]=Dist1[Now];
			Dist1[Now]=Dist1[Next]+e.dist;
		} else if(Dist1[Next]+e.dist>Dist2[Now])Dist2[Now]=Dist1[Next]+e.dist;
	}
	if(Square[Now]) { //方点
		deque<int>Q;
		int cnt=0;
		a[++cnt]=0;
		for(Edge& e:tree[Now])a[++cnt]=Dist1[e.to];
		for(int i=1; i<=cnt; i++)a[cnt+i]=a[i];
		cnt*=2;
		Q.push_back(1);
		for(int i=2; i<=cnt; i++) {
			while(!Q.empty()&&i-Q.front()>cnt/4)Q.pop_front();
			ans=max(ans,a[i]+i+a[Q.front()]-Q.front());
			while(!Q.empty()&&a[Q.back()]-Q.back()<=a[i]-i)Q.pop_back();
			Q.push_back(i);
		}
	} else ans=max(ans,Dist1[Now]+Dist2[Now]);
}

int main() {
	New=n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		int k=Get_Int(),last=0;
		while(k--) {
			int x=Get_Int();
			if(!last) {
				last=x;
				continue;
			}
			AddEdge(x,last);
			AddEdge(last,x);
			last=x;
		}
	}
	Tarjan(1,0);
	TreeDp(1);
	printf("%d\n",ans);
	return 0;
}