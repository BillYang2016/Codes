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

int n,q;
bool bj=0;

struct Graph {
	int Degree[maxn],father[maxn],del,cir,cirsize;
	bool d3;
	vector<int> edges[maxn];
	void init(int del=0) {
		for(int i=1; i<=n; i++)father[i]=-1;
		this->del=del;
	}
	int Get_Father(int x) {return father[x]<0?x:father[x]=Get_Father(father[x]);}
	void link(int x,int y) {
		if(x==del||y==del)return;
		Degree[x]++,Degree[y]++;
		edges[x].push_back(y),edges[y].push_back(x);
		if(Degree[x]>=3||Degree[y]>=3)d3=1;
		int fx=Get_Father(x),fy=Get_Father(y);
		if(fx==fy) {cir++;cirsize=-father[fx];}
		else {father[fy]+=father[fx];father[fx]=fy;}
	}
} G[5];

void build(int p,int id) {
	G[id].init(p);
	for(int Now=1; Now<=n; Now++)
		for(int Next:G[0].edges[Now])
			if(Now>Next)G[id].link(Now,Next);
}

void split() {
	int p=0,cnt=0;
	for(int i=1; i<=n; i++)if(G[0].Degree[i]>=3)p=i;
	for(int Next:G[0].edges[p])build(Next,++cnt);
	build(p,++cnt);
}

int Query() {
	if(G[0].cir>1)return 0;
	else if(G[0].d3==0)return !G[0].cir?n:G[0].cirsize;
	else {
		int ans=0;
		for(int i=1; i<=4; i++)if(!G[i].cir&&!G[i].d3)ans++;
		return ans;
	}
}

int main() {
	n=Get_Int();
	q=Get_Int();
	G[0].init();
	for(int i=1; i<=q; i++) {
		char opt=' ';
		while(!isalpha(opt))opt=getchar();
		if(opt=='Q') {
			if(bj)puts("0");
			else {
				int x=Query();
				if(!x)bj=1;
				printf("%d\n",x);
			}
		} else {
			int x=Get_Int(),y=Get_Int();
			if(bj)continue;
			if(G[0].d3==0) {
				G[0].link(x,y);
				if(G[0].d3)split();
			} else for(int i=1; i<=4; i++)G[i].link(x,y);
		}
	}
	return 0;
}