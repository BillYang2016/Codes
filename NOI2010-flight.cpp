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

const int maxn=2005;

int n,m,k[maxn],InDegree[maxn],tmp[maxn],Ans[maxn],cnt=0; 
vector<int>edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

struct HeapNode {
	int k,u;
	HeapNode(int _k=0,int _u=0):k(_k),u(_u) {}
	bool operator < (const HeapNode& b) const {
		return k<b.k;
	}
};

int Solve(int x) {
	memcpy(tmp,InDegree,sizeof(InDegree));
	tmp[x]=n;
	priority_queue<HeapNode>Q;
	for(int i=1; i<=n; i++)
		if(!tmp[i])Q.push(HeapNode(k[i],i));
	for(int i=n; i>=1; i--) {
		if(Q.empty()||Q.top().k<i)return i;
		int Now=Q.top().u;
		Q.pop();
		for(int Next:edges[Now]) {
			tmp[Next]--;
			if(!tmp[Next])Q.push(HeapNode(k[Next],Next));
		}
	}
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)k[i]=Get_Int();
	for(int i=1; i<=m; i++) {
		int x=Get_Int(),y=Get_Int();
		AddEdge(y,x);
		InDegree[x]++;
	}
	memcpy(tmp,InDegree,sizeof(InDegree));
	priority_queue<HeapNode>Q;
	for(int i=1; i<=n; i++)
		if(!tmp[i])Q.push(HeapNode(k[i],i));
	while(!Q.empty()) {
		int Now=Q.top().u;
		Q.pop();
		Ans[++cnt]=Now;
		for(int Next:edges[Now]) {
			tmp[Next]--;
			if(!tmp[Next])Q.push(HeapNode(k[Next],Next));
		}
	}
	for(int i=cnt; i>=1; i--)printf("%d ",Ans[i]);
	putchar('\n');
	for(int i=1; i<=n; i++)printf("%d ",Solve(i));
	return 0;
} 
