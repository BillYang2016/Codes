#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxd=205,maxn=5005,maxs=262143,Base=10007;

struct node {
	LL v;
	int num;
	node(LL v=0,int num=0):v(v),num(num) {}
};

list<node> L[maxs+1];
vector<int> edges[maxd][maxn];
LL Hash[maxn],Pow[maxd],f[maxd][maxn],size[maxd][maxn];
int ans=0;

void ins(LL v) {
	int pos=v&maxs;
	for(auto &x:L[pos])if(x.v==v) {ans+=x.num*2+1;x.num++;return;}
	ans++,L[pos].push_back(node(v,1));
}

void del(LL v) {
	int pos=v&maxs;
	for(auto it=L[pos].begin(); it!=L[pos].end(); it++) {
		auto &x=*it;
		if(x.v!=v)continue;
		ans-=(x.num-1)*2+1;
		if(--x.num==0)L[pos].erase(it);
		return;
	}
}

void Dfs(int z,int x,int fa,int id) {
	del(Hash[x]),Hash[x]-=Pow[z]*f[z][x];
	f[z][x]=id;
	Hash[x]+=Pow[z]*id,ins(Hash[x]);
	for(int y:edges[z][x])if(y!=fa)Dfs(z,y,x,id);
}

void merge(int z,int x,int y) {
	if(f[z][x]==f[z][y])return;
	if(size[z][f[z][x]]>size[z][f[z][y]])swap(x,y);
	size[z][f[z][y]]+=size[z][f[z][x]];
	edges[z][x].push_back(y),edges[z][y].push_back(x);
	Dfs(z,x,y,f[z][y]);
}

int d,n,m;

int main() {
	d=Get_Int();
	n=Get_Int();
	m=Get_Int();
	Pow[0]=1;
	for(int i=1; i<d; i++)Pow[i]=Pow[i-1]*Base;
	for(int i=1; i<=n; ins(Hash[i++]))
		for(int j=0; j<d; j++)f[j][i]=i,size[j][i]=1,Hash[i]+=Pow[j]*i;
	while(m--) {
		int x=Get_Int(),y=Get_Int(),z=Get_Int();
		merge(--z,x,y);
		printf("%d\n",ans);
	}
	return 0;
}