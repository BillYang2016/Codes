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
#include<map>
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

const int maxn=4005;

int n,m,My[maxn],Man;
bool vst[maxn];
vector<int>edges[maxn];

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

bool Dfs(int Now) {
	for(int Next:edges[Now]) {
		if(vst[Next]||(Next==Man&&Now==Man))continue;
		vst[Next]=1;
		if(My[Next]==0||Dfs(My[Next])) { //可增广
			My[Next]=Now;
			return true;
		}
	}
	return false;
}

string s1,s2;
map<string,int>M;

int main() {
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>s1>>s2;
		M[s1]=M[s2]=i;
		AddEdge(i,i);
		My[i]=i;
	}
	cin>>m;
	for(int i=1; i<=m; i++) {
		cin>>s1>>s2;
		AddEdge(M[s1],M[s2]);
	}
	for(int i=1; i<=n; i++) {
		memset(vst,0,sizeof(vst));
		My[i]=0;
		Man=i;
		if(Dfs(i))puts("Unsafe");
		else puts("Safe");
		for(int j=1; j<=n; j++)My[j]=j;
	}
	return 0;
}