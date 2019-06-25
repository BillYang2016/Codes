#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=10005,maxk=12;

struct Edge {
	int from,to,dist;
	Edge(int x,int y,int z):from(x),to(y),dist(z) {}
};

typedef pair<int,int> pii;
#define mp make_pair

vector<Edge> edges;
vector<int> G[maxn];
int n,m,k,s,t,dist[maxn][maxk];
bool inque[maxn][maxk];

void AddEdge(int x,int y,int v) {
	edges.push_back(Edge(x,y,v));
	G[x].push_back(edges.size()-1);
	edges.push_back(Edge(y,x,v));
	G[y].push_back(edges.size()-1);
}

void Spfa() {
	for(int i=1; i<=n; i++)
		for(int j=0; j<=k; j++)dist[i][j]=INT_MAX/2;
	deque<pii> Q;
	Q.push_back(mp(s,0));
	for(int i=0; i<=k; i++)dist[s][i]=0;
	inque[s][0]=1;
	while(!Q.empty()) {
		int Now=Q.front().first,Nowk=Q.front().second;
		Q.pop_front();
		inque[Now][Nowk]=0;
		for(int i=0; i<G[Now].size(); i++) {
			Edge &e=edges[G[Now][i]];
			int Next=e.to;
			if(dist[Next][Nowk]>dist[Now][Nowk]+e.dist) {
				dist[Next][Nowk]=dist[Now][Nowk]+e.dist;
				if(!inque[Next][Nowk]) {
					if(!Q.empty()&&dist[Next][Nowk]<dist[Q.front().first][Q.front().second])Q.push_front(mp(Next,Nowk));
					else Q.push_back(mp(Next,Nowk));
					inque[Next][Nowk]=1;
				}
			}
			if(Nowk<k&&dist[Next][Nowk+1]>dist[Now][Nowk]) {
				dist[Next][Nowk+1]=dist[Now][Nowk];
				if(!inque[Next][Nowk+1]) {
					if(!Q.empty()&&dist[Next][Nowk+1]<dist[Q.front().first][Q.front().second])Q.push_front(mp(Next,Nowk+1));
					else Q.push_back(mp(Next,Nowk+1));
					inque[Next][Nowk+1]=1;
				}
			}
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	k=Get_Int();
	s=Get_Int()+1;
	t=Get_Int()+1;
	for(int i=1; i<=m; i++) {
		int x=Get_Int()+1,y=Get_Int()+1,z=Get_Int();
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Spfa();
	int ans=dist[t][0];
	for(int i=1; i<=k; i++)ans=min(ans,dist[t][i]);
	printf("%d\n",ans);
	return 0;
} 
