#include<bits/stdc++.h>

using namespace std;

inline int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(!isdigit(x)) {if(x=='-')bj=-1;x=getchar();}
	while(isdigit(x)) {num=num*10+x-'0';x=getchar();}
	return num*bj;
}

const int maxn=2000005;

int n,m,a[maxn],f[maxn];
vector<int> edges[maxn];

void Dfs(int Now) {
	for(int Next:edges[Now]) {
		Dfs(Next);
		a[Now]++;
		f[Now]+=f[Next];
	}
	vector<int> tmp;
	for(int Next:edges[Now])tmp.push_back(a[Next]);
	sort(tmp.begin(),tmp.end());
	for(int x:tmp)
		if(a[Now]+x-1<=m)a[Now]+=x-1,f[Now]++;
		else break;
}

int main() {
	n=Get_Int();
	m=Get_Int();
	for(int i=1; i<=n; i++)a[i]=Get_Int();
	for(int i=1; i<=n; i++) {
		int l=Get_Int();
		while(l--)edges[i].push_back(Get_Int()+1);
	}
	Dfs(1);
	printf("%d\n",f[1]);
	return 0;
}