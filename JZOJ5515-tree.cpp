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

const int maxn=30005;

int father[maxn],prt[maxn];
vector<int> edges[maxn];

void Dfs(int Now,int fa) {
	father[Now]=fa;
	for(int Next:edges[Now])if(Next!=fa)Dfs(Next,Now);
}

int Get_Father(int x) {return prt[x]==x?x:prt[x]=Get_Father(prt[x]);}

struct node {
	int p,size;
	LL sum;
	node(LL p=0,LL s=0,LL s2=0):p(p),size(s),sum(s2) {}
	bool operator < (const node &b) const {return sum*b.size<b.sum*size||(sum*b.size==b.sum*size&&p>b.p);}
};

int n,size[maxn];
LL a[maxn],sum[maxn],Ans=0;
vector<int> root;
set<node> S;

int main() {
	n=Get_Int();
	for(int i=1; i<n; i++) {
		int x=Get_Int(),y=Get_Int();
		edges[x].push_back(y);
		edges[y].push_back(x);
	}
	for(int i=1; i<=n; i++) {
		a[i]=Get_Int();
		if(Get_Int())root.push_back(i);
	}
	for(int x:root) {
		Dfs(x,0);
		LL ans=0;
		for(int i=1; i<=n; i++) {
			S.insert(node(i,size[i]=1,sum[i]=a[i]));
			ans+=a[i];
			prt[i]=i;
		}
		while(!S.empty()) {
			node now=*S.begin();
			S.erase(S.begin());
			if(now.p==x)continue;
			int fp=Get_Father(father[now.p]);
			ans+=size[fp]*sum[now.p];
			S.erase(node(fp,size[fp],sum[fp]));
			size[fp]+=size[now.p],sum[fp]+=sum[now.p];
			S.insert(node(prt[now.p]=fp,size[fp],sum[fp]));
		}
		Ans=max(Ans,ans);
	}
	printf("%lld\n",Ans);
	return 0;
}