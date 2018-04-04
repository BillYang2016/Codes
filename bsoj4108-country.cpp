#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=55;

struct Edge {
	int from,to;
	LL dist;
	Edge(int x=0,int y=0,LL v=0):from(x),to(y),dist(v) {}
	bool operator < (const Edge &b) const {return dist<b.dist;}
};

int n,father[maxn];
LL C,T[maxn],U[maxn],F[maxn],ans=0;
char a[maxn][maxn];
vector<Edge> edges;

int Get_Father(int x) {return father[x]==x?x:father[x]=Get_Father(father[x]);}

void Union(int x,int y) {
	int fx=Get_Father(x),fy=Get_Father(y);
	if(fx!=fy)father[fx]=fy;
}

LL Cal(LL x,LL y) {return (U[x]-T[x])*T[y]*F[x]+(U[y]-T[y])*U[x]*F[y];} //先x后y

int main() {
	n=Get_Int();
	for(int i=1; i<=n; i++)T[i]=Get_Int();
	for(int i=1; i<=n; i++)U[i]=Get_Int();
	for(int i=1; i<=n; i++)F[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		father[i]=i;
		ans+=(U[i]+T[i]-1)*(U[i]-T[i])/2*F[i];
	}
	for(int i=1; i<=n; i++)scanf("%s",a[i]+1);
	C=Get_Int();
	for(int i=1; i<=n; i++)
		for(int j=i+1; j<=n; j++)
			if(a[i][j]=='Y') {
				ans+=min(Cal(i,j),Cal(j,i));
				Union(i,j);
			} else edges.push_back(Edge(i,j,C*(T[i]+T[j])+min(Cal(i,j),Cal(j,i))));
	sort(edges.begin(),edges.end());
	for(Edge &e:edges) {
		int fx=Get_Father(e.from),fy=Get_Father(e.to);
		if(fx==fy)continue;
		ans+=e.dist;
		father[fx]=fy;
	}
	printf("%lld\n",ans);
	return 0;
}