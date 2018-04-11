#include<bits/stdc++.h>

using namespace std;

namespace FastIO {
	const int L=1<<15;
	char buffer[L],*S,*T;
	inline int Get_Int() {
		int num=0,bj=1;
		char x=getchar();
		while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
		while(isdigit(x)) {num=(num<<1)+(num<<3)+x-'0';x=getchar();}
		return num*bj;
	}
	inline void Put_Int(int x) {
		if(x<0)putchar('-'),x=-x;
		if(x>9)Put_Int(x/10);
		putchar(x%10+'0');
	}
}

using namespace FastIO;

const int maxn=100005,maxm=2000005,K=21;

int pos[maxn];

struct Aho_Corasick_Automaton {
	struct Tree {int child[26],fail;} tree[maxm];
	int cnt;
#define ch(x,i) tree[x].child[i]
#define fail(x) tree[x].fail
	int newnode() {return ++cnt;}
	void insert(string s,int id) {
		int now=0;
		for(char x:s) {
			int j=x-'a';
			if(!ch(now,j))ch(now,j)=newnode();
			now=ch(now,j);
		}
		pos[id]=now;
	}
	void buildfail() {
		queue<int> Q;
		Q.push(0);
		while(!Q.empty()) {
			int now=Q.front();
			Q.pop();
			for(int i=0; i<26; i++) {
				int &Next=ch(now,i);
				if(Next) {
					if(now)fail(Next)=ch(fail(now),i);
					Q.push(Next);
				} else Next=ch(fail(now),i);
			}
		}
	}
} acam;

int step=0,cnt=0,First[maxm],Last[maxm],Depth[maxm],p[maxm][K],Head[maxm];
struct Edge {int to,Next;} edges[maxm];

void AddEdge(int x,int y) {
	edges[++cnt].to=y;
	edges[cnt].Next=Head[x];
	Head[x]=cnt;
}

void Dfs(int Now,int fa,int depth) {
	First[Now]=++step;
	Depth[Now]=depth;
	p[Now][0]=fa;
	for(int i=Head[Now]; i; i=edges[i].Next)Dfs(edges[i].to,Now,depth+1);
	Last[Now]=step;
}

void Sparse_Table() {
	for(int j=1; j<K; j++)
		for(int i=1; i<=acam.cnt; i++)
			if(~p[i][j-1])p[i][j]=p[p[i][j-1]][j-1];
}

int LCA(int a,int b) {
	if(Depth[a]<Depth[b])swap(a,b);
	for(int i=K-1; i>=0; i--)if(Depth[a]-(1<<i)>=Depth[b])a=p[a][i];
	if(a==b)return a;
	for(int i=K-1; i>=0; i--)if(p[a][i]!=p[b][i])a=p[a][i],b=p[b][i];
	return p[a][0];
}

struct BIT {
	int c[maxm];
#define lowbit(x) (x&(-x))
	void add(int x,int v) {
		for(int i=x; i<=step; i+=lowbit(i))c[i]+=v;
	}
	int query(int x) {
		int ans=0;
		for(int i=x; i>=1; i-=lowbit(i))ans+=c[i];
		return ans;
	}
} bit;

bool cmp(int x,int y) {return First[x]<First[y];}

int n,a[maxm];
char s[maxm];

int main() {
	memset(p,-1,sizeof(p));
	n=Get_Int();
	for(int i=1; i<=n; i++) {
		scanf("%s",s);
		acam.insert(s,i);
	}
	acam.buildfail();
	for(int i=1; i<=acam.cnt; i++)AddEdge(acam.tree[i].fail,i);
	Dfs(0,-1,1);
	Sparse_Table();
	int q=Get_Int();
	while(q--) {
		int opt=Get_Int();
		if(opt==1) {
			scanf("%s",s);
			int len=strlen(s),now=0,num=0;
			for(int i=0; i<len; i++) {
				now=acam.tree[now].child[s[i]-'a'];
				if(now)a[++num]=now;
			}
			sort(a+1,a+num+1,cmp);
			for(int i=1; i<=num; i++)bit.add(First[a[i]],1);
			for(int i=1; i<num; i++)bit.add(First[LCA(a[i],a[i+1])],-1);
		} else {
			int x=Get_Int();
			Put_Int(bit.query(Last[pos[x]])-bit.query(First[pos[x]]-1));
			putchar('\n');
		}
	}
	return 0;
}