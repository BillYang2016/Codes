#include<bits/stdc++.h>

using namespace std;

const int maxn=800005;

int cnt=0,Head[maxn<<1],Tail[maxn<<1],father[maxn];

struct Edge {
	int from,to,next;
} Edge[maxn<<2];

void AddEdge(int x,int y) {
	cnt++;
	Edge[cnt].from=x;
	Edge[cnt].to=y;
	if(!Head[x])Tail[x]=cnt;
	Edge[cnt].next=Head[x];
	Head[x]=cnt;
}

void Merge(int x,int y) { //x的边集合并到y
	if(!Tail[y]) {
		Head[y]=Head[x];
		Tail[y]=Tail[x];
		return;
	}
	Edge[Tail[y]].next=Head[x];
	Tail[y]=Tail[x];
}

int getfa(int x) {return x==father[x]?x:father[x]=getfa(father[x]);}

int t,n,m,q;

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		cnt=0;
		for(int i=1; i<=2*n; i++)Head[i]=Tail[i]=0;
		for(int i=1; i<=m; i++) {
			int x,y;
			scanf("%d%d",&x,&y);
			x++,y++;
			AddEdge(x,y);
			AddEdge(y,x);
		}
		for(int i=1; i<=n; i++)Merge(i,n+i),father[i]=i;
		scanf("%d",&q);
		for(int i=1; i<=q; i++) {
			int x;
			scanf("%d",&x);
			x++;
			if(x!=getfa(x))continue;
			vector<int> tmp;
			for(int i=Head[n+x]; i; i=Edge[i].next) {
				int from=Edge[i].from,to=Edge[i].to;
				int fx=getfa(from),fy=getfa(to);
				Head[n+x]=Edge[i].next;
				if(fx==fy)continue;
				father[fy]=fx;
				tmp.push_back(n+fy);
			}
			Tail[n+x]=0;
			for(int y:tmp)Merge(y,n+x);
		}
		for(int i=1; i<=n; i++)printf("%d ",getfa(i)-1);
		putchar('\n');
	}
	return 0;
}