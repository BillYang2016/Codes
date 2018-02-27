#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;

typedef long long LL;

inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=200005,maxm=25005,maxb=455;

int n,m,q,step=0,S[maxn],Hash[maxm],Color[maxn],First[maxn],Last[maxn];
LL Up[maxm][maxb],Down[maxm][maxb];
vector<int>Col[maxm],edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Dfs(int Now) {
	First[Now]=++step;
	Col[Color[Now]].push_back(Now);
	for(int Next:edges[Now])Dfs(Next);
	Last[Now]=step;
}

int Solve(int Now,int col,int times) {
	if(Color[Now]==col)times++;
	else Up[Color[Now]][Hash[col]]+=times;
	int tmp=0;
	if(Color[Now]==col)tmp++;
	for(int Next:edges[Now])tmp+=Solve(Next,col,times);
	if(Color[Now]!=col)Down[Color[Now]][Hash[col]]+=tmp;
	return tmp;
}

bool cmp(int a,int b) {
	return First[a]<First[b];
}

LL Query(int x,int y) {
	if(Hash[x])return Up[y][Hash[x]];
	if(Hash[y])return Down[x][Hash[y]];
	vector<int>p;
	p.resize(Col[x].size()+Col[y].size());
	merge(Col[x].begin(),Col[x].end(),Col[y].begin(),Col[y].end(),p.begin(),cmp);
	int top=0,tot=0;
	LL ans=0;
	for(int now:p) {
		while(top>0&&(First[now]<First[S[top]]||Last[now]>Last[S[top]])) {
			tot-=Color[S[top]]==x;
			top--;
		}
		ans+=tot*(Color[now]==y);
		S[++top]=now;
		tot+=Color[now]==x;
	}
	return ans;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	q=Get_Int();
	Color[1]=Get_Int();
	for(int i=2; i<=n; i++) {
		AddEdge(Get_Int(),i);
		Color[i]=Get_Int();
	}
	Dfs(1);
	int size=sqrt(n),BCC=0;
	for(int i=1; i<=m; i++)
		if(Col[i].size()>size) {
			Hash[i]=++BCC;
			Solve(1,i,0);
		}
	for(int i=1; i<=q; i++) {
		int x=Get_Int(),y=Get_Int();
		printf("%lld\n",Query(x,y));
	}
	return 0;
}