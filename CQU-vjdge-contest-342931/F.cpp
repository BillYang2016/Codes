#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=105;

struct Union_Set {
	int n,father[maxn];
	void init(int n) {
		this->n=n;
		for(int i=1; i<=n; i++)father[i]=i;
	}
	int get(int x) {return father[x]==x?x:father[x]=get(father[x]);}
	void merge(int x,int y) {
		x=get(x);
		y=get(y);
		if(x==y)return;
		father[x]=y;
	}
	bool query(int x,int y) {return get(x)==get(y);}
} st[maxn];

int n,m,q;

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=m; i++)st[i].init(n);
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int(),v=Get_Int();
		st[v].merge(x,y);
	}
	q=Get_Int();
	while(q--) {
		int ans=0,x=Get_Int(),y=Get_Int();
		for(int i=1; i<=m; i++)ans+=st[i].query(x,y);
		printf("%d\n",ans);
	}
	return 0;
}