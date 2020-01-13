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

typedef long long LL;

int n,Size[maxn],Son[maxn];
LL Ans[maxn];
vector<int> edges[maxn];

void Dfs(int Now) {
	Size[Now]=1;
	for(int Next:edges[Now]) {
		Dfs(Next);
		Size[Now]+=Size[Next];
		if(Size[Next]>Size[Son[Now]])Son[Now]=Next;
	}
}

void Add(int Now,set<int> &S,int x) {
	auto pre=S.lower_bound(x),suc=S.upper_bound(x); //用的前提是x不在set中
	if(pre==S.begin()) { //set里面找不到小于x的
		if(suc!=S.end())Ans[Now]+=1ll*x*x+1ll*(*suc)*(*suc)-1ll*2*x*(*suc);
	} else { //有前驱
		pre--;
		if(suc!=S.end())Ans[Now]+=1ll*2*x*x+1ll*2*(*pre)*(*suc)-1ll*2*x*(*pre)-1ll*2*x*(*suc); //有前驱后继
		else Ans[Now]+=1ll*x*x+1ll*(*pre)*(*pre)-1ll*2*x*(*pre); //有前驱无后继
	}
	S.insert(x);
}

void Dfs(int Now,set<int> &S) {
	if(Son[Now]) {
		Dfs(Son[Now],S);
		Ans[Now]=Ans[Son[Now]];
	}
	for(int Next:edges[Now]) {
		if(Next==Son[Now])continue;
		set<int> tmp;
		Dfs(Next,tmp);
		for(auto x:tmp)Add(Now,S,x);
	}
	Add(Now,S,Now);
}

int main() {
	n=Get_Int();
	for(int i=2; i<=n; i++)edges[Get_Int()].push_back(i);
	Dfs(1);
	set<int> S;
	Dfs(1,S);
	for(int i=1; i<=n; i++)printf("%lld\n",Ans[i]);
	return 0;
}