#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=30005;

struct Edge {int from,to,ch;};
vector<Edge> edges[maxn];
bitset<(maxn<<1)> f[maxn],g[maxn],ans,tmpf,tmpg,ch[26];
int father[maxn],dis[maxn],InDegree[maxn];

void AddEdge(int x,int y,char v) {edges[x].push_back((Edge) {x,y,v-'a'});}

void Dfs(int Now,int fa) {
	father[Now]=fa;
	for(Edge &e:edges[Now]) {
		int Next=e.to;
		if(Next==fa)continue;
		Dfs(Next,Now);
		InDegree[Now]++;
		dis[Next]=e.ch;
	}
}

int n,m,l[maxn],r[maxn];
char s[maxn];

void Bfs() {
	queue<int> Q;
	for(int i=1; i<=n; i++)if(!InDegree[i])Q.push(i);
	while(!Q.empty()) {
		int Now=Q.front();
		Q.pop();
		if(Now==1)break;
		int Next=father[Now];
		tmpf=(f[Now]<<1)&ch[dis[Now]];
		tmpg=(g[Now]>>1)&ch[dis[Now]];
		ans|=(f[Next]<<1)&tmpg;
		ans|=tmpf&(g[Next]>>1);
		f[Next]|=tmpf;
		g[Next]|=tmpg;
		if(--InDegree[Next]==0)Q.push(Next);
	}
}

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		char v=' ';
		while(!isalpha(v))v=getchar();
		AddEdge(x,y,v);
		AddEdge(y,x,v);
	}
	m=Get_Int();
	r[0]=1;
	for(int i=1; i<=m; i++) {
		scanf("%s",s+1);
		int len=strlen(s+1);
		l[i]=r[i-1]+1,r[i]=r[i-1]+len;
		for(int j=1; j<=len; j++)ch[s[j]-'a'].set(r[i-1]+j);
		r[i]++; //空字符
	}
	for(int i=0; i<=m; i++)f[0].set(r[i]);
	g[0]=f[0];
	for(int i=1; i<=n; i++)f[i]=g[i]=f[0];
	Dfs(1,0);
	Bfs();
	for(int i=1; i<=m; i++) {
		bool bj=0;
		for(int j=l[i]; j<r[i]; j++)bj|=ans[j];
		puts(bj?"YES":"NO");
	}
	return 0;
}