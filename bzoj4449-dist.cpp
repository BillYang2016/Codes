#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=110005;

struct Edge {int from,to;} edge[maxn],le[maxn],re[maxn];
struct Query {int x,y,id;} q[maxn<<1],lq[maxn<<1],rq[maxn<<1];
vector<int> edges[maxn];
int p[maxn],lp[maxn],rp[maxn];

void Bfs(int s,int pl,int pr,int *dist) {
	queue<int> Q;
	for(int i=pl; i<=pr; i++)dist[p[i]]=INT_MAX/2;
	Q.push(s);
	dist[s]=0;
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		for(int Next:edges[Now]) {
			if(!binary_search(p+pl,p+pr+1,Next))continue;
			if(dist[Next]==INT_MAX/2) {
				dist[Next]=dist[Now]+1;
				Q.push(Next);
			}
		}
	}
}

int dist1[maxn],dist2[maxn],ans[maxn];

void Binary(int xl,int xr,int pl,int pr,int ql,int qr) {
	if(xl>xr||pl>pr||ql>qr)return;
	int Min=INT_MAX/2,pos=0,len=pr-pl+1;
	for(int i=xl; i<=xr; i++) {
		int px=lower_bound(p+pl,p+pr+1,edge[i].from)-p-(pl-1),py=lower_bound(p+pl,p+pr+1,edge[i].to)-p-(pl-1);
		if(px>py)swap(px,py);
		if(max(py-px,px+len-py)<Min) {Min=max(py-px,px+len-py);pos=i;}
	}
	Bfs(edge[pos].from,pl,pr,dist1);
	Bfs(edge[pos].to,pl,pr,dist2);
	int lqpos=0,rqpos=0;
	for(int i=ql; i<=qr; i++) { //询问
		if(q[i].x==edge[pos].from&&q[i].y==edge[pos].to) {ans[q[i].id]=1;continue;}
		ans[q[i].id]=min({ans[q[i].id],dist1[q[i].x]+dist1[q[i].y],dist2[q[i].x]+dist2[q[i].y],dist1[q[i].x]+1+dist2[q[i].y],dist1[q[i].y]+1+dist2[q[i].x]});
		if(q[i].x>edge[pos].from&&q[i].y<edge[pos].to)lq[++lqpos]=q[i];
		if((q[i].x<edge[pos].from||q[i].x>edge[pos].to)&&(q[i].y<edge[pos].from||q[i].y>edge[pos].to))rq[++rqpos]=q[i];
	}
	for(int i=1; i<=lqpos; i++)q[ql+i-1]=lq[i];
	for(int i=1; i<=rqpos; i++)q[ql+lqpos+i-1]=rq[i];
	int lppos=0,rppos=0;
	for(int i=pl; i<=pr; i++) { //点
		if(p[i]>=edge[pos].from&&p[i]<=edge[pos].to)lp[++lppos]=p[i];
		if(p[i]<=edge[pos].from||p[i]>=edge[pos].to)rp[++rppos]=p[i];
	}
	for(int i=1; i<=lppos; i++)p[pl+i-1]=lp[i];
	for(int i=1; i<=rppos; i++)p[pl+lppos+i-1]=rp[i];
	int lepos=0,repos=0;
	for(int i=xl; i<=xr; i++)if(i!=pos) { //剖分边
		if(edge[i].from>=edge[pos].from&&edge[i].from<=edge[pos].to&&edge[i].to>=edge[pos].from&&edge[i].to<=edge[pos].to)le[++lepos]=edge[i];
		else re[++repos]=edge[i];
	}
	for(int i=1; i<=lepos; i++)edge[xl+i-1]=le[i];
	for(int i=1; i<=repos; i++)edge[xl+lepos+i-1]=re[i];
	Binary(xl+lepos,xl+lepos+repos-1,pl+lppos,pl+lppos+rppos-1,ql+lqpos,ql+lqpos+rqpos-1);
	Binary(xl,xl+lepos-1,pl,pl+lppos-1,ql,ql+lqpos-1);
}

int n,m;

int main() {
	n=Get_Int();
	for(int i=1; i<=n-3; i++) {
		int x=Get_Int(),y=Get_Int();
		if(x>y)swap(x,y);
		edge[i]=(Edge) {x,y};
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	for(int i=1; i<n; i++)edges[i].push_back(i+1),edges[i+1].push_back(i);
	edges[1].push_back(n),edges[n].push_back(1);
	m=Get_Int();
	for(int i=1; i<=m; i++) {
		q[i].x=Get_Int();
		q[i].y=Get_Int();
		if(q[i].x>q[i].y)swap(q[i].x,q[i].y);
		ans[i]=min(q[i].y-q[i].x,q[i].x+n-q[i].y);
		q[i].id=i;
	}
	for(int i=1; i<=n; i++)p[i]=i;
	Binary(1,n-3,1,n,1,m);
	for(int i=1; i<=m; i++)printf("%d\n",ans[i]);
	return 0;
}