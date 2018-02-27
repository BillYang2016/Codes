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
	while(!isdigit(x)) {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(isdigit(x)) {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}

const int maxn=35;

#define pii pair<int,int>
#define mp make_pair

char s1[100005],s2[100005];
bool vst[maxn];
vector<int> edges[maxn]; 
vector<pii> ans;
int n;

void AddEdge(int x,int y) {
	edges[x].push_back(y);
}

void Dfs(int Now) {
	vst[Now]=1;
	for(int Next:edges[Now]) {
		if(vst[Next])continue;
		ans.push_back(mp(Now,Next));
		Dfs(Next);
	}
}

int main() {
	n=Get_Int();
	scanf("%s%s",s1+1,s2+1);
	for(int i=1; i<=n; i++)
		if(s1[i]!=s2[i]) {
			AddEdge(s1[i]-'a',s2[i]-'a');
			AddEdge(s2[i]-'a',s1[i]-'a');
		}
	for(int i=0; i<26; i++)if(!vst[i])Dfs(i);
	printf("%d\n",ans.size());
	for(pii x:ans)printf("%c %c\n",x.first+'a',x.second+'a');
	return 0;
}